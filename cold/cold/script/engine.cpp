#include "engine.h"

#include <cold/script/compile/parse.h>
#include <cold/script/compile/compile.h>
#include <cold/script/object_instance.h>
#include <cold/script/function_instance.h>
#include <cold/script/function_definition.h>
#include <cold/script/list_instance.h>
#include <cold/script/list.h>
#include <cold/script/param_list.h>

namespace cold { namespace script {

Engine::Engine(unsigned int stack_size)
	: stack(stack_size)
{
	call_stack.push_back(Call(NULL));
}
Engine::~Engine() {
	for (std::vector<Instance*>::iterator it = instances.begin(); it != instances.end(); ++it) {
		delete *it;
	}
}

Value Engine::get_global(const std::string& name) {
	return call_stack.front().context[name];
}

void Engine::set_global(const std::string& name, const Value& v) {
	call_stack.front().context[name] = v;
}

Object Engine::create_object() {
	ObjectInstance *i = new ObjectInstance(this);
	instances.push_back(i);
	return Object(i);
}
List Engine::create_list() {
	ListInstance *i = new ListInstance(this, std::vector<Value>());
	instances.push_back(i);
	return List(i);
}

Value Engine::add_instance(Instance *i) {
	instances.push_back(i);
	return i;
}

void Engine::mark_and_push(std::stack<Instance*>& w, const SizedStack<Value>& i) {
	for (const Value* it = i.cbegin(); it != i.cend(); ++it) {
		if (it->type == Value::OBJECT && !it->data.v_inst->mark) {
			it->data.v_inst->mark = true;
			w.push(it->data.v_inst);
		}
	}
}
void Engine::mark_and_push(std::stack<Instance*>& w, const std::map<std::string, Value>& i) {
	for (std::map<std::string, Value>::const_iterator it = i.cbegin(); it != i.cend(); ++it) {
		if (it->second.type == Value::OBJECT && !it->second.data.v_inst->mark) {
			it->second.data.v_inst->mark = true;
			w.push(it->second.data.v_inst);
		}
	}
}

void Engine::collect_garbage() {
	std::stack<Instance*> work;
	for (std::vector<Instance*>::iterator it = instances.begin(); it != instances.end(); ++it) {
		if ((*it)->unmanaged_ptr_count) {
			(*it)->mark = true;
			work.push(*it);
		}
	}
	for (std::vector<Call>::iterator it = call_stack.begin(); it != call_stack.end(); ++it) {
		mark_and_push(work, it->context);	
	}
	mark_and_push(work, stack);
	while (!work.empty()) {
		if (work.top()->get_type() == Instance::OBJECT)
			mark_and_push(work, work.top()->cast<ObjectInstance>()->values);
		work.pop();
	}
	for (std::vector<Instance*>::iterator it = instances.begin(); it != instances.end();) {
		if ((*it)->mark) {
			(*it)->mark = false;
			++it;
		} else {
			delete *it;
			it = instances.erase(it);
		}
	}
}

namespace {
	struct CallPtr {
		CallPtr(
			std::vector<Instruction>::const_iterator r,
			std::vector<Instruction>::const_iterator e)
			: ret(r), end(e) { }

		std::vector<Instruction>::const_iterator ret, end;
	};
}

void Engine::run(const std::vector<Instruction>& i) {
	std::stack<CallPtr> cptr_stack;
	std::vector<Instruction>::const_iterator pc = i.cbegin(), end = i.cend();
	goto interp_begin;
	while (cptr_stack.size()) {
		pc = cptr_stack.top().ret;
		end = cptr_stack.top().end;
		cptr_stack.pop();
interp_begin:
		while (pc != end) {
			switch (pc->type) {
			case Instruction::GET_NAME:
				push(get_name(pc->data.name));
				break;
			case Instruction::GET_NAME_REF:
				push(&get_name(pc->data.name));
				break;
			case Instruction::GET_MEMBER: {
				// TODO(bqq): Error handling
				Value v;
				pop().data.v_inst->get_member(&v, pc->data.name);
				push(v);
				//push(pop().data.v_inst->cast<ObjectInstance>()->values[pc->data.name]);
				} break;
			case Instruction::GET_MEMBER_REF:
				push(&pop().data.v_inst->cast<ObjectInstance>()->values[pc->data.name]);
				break;
			case Instruction::FUNCTION: {
				FunctionInstance *fi = new FunctionInstance(this, func_defs[pc->data.func]);
				instances.push_back(fi);
				push(fi);
				} break;
			case Instruction::OP: {
				Value b = pop();
				Value a = pop();
				switch (pc->data.op) {
				case '+' : push(a + b); break;
				case '-' : push(a - b); break;
				case '*' : push(a * b); break;
				case '/' : push(a / b); break;
				case '%' : push(a % b); break;
				}
				} break;
			case Instruction::INT_CONST:
				push(pc->data.v_int);
				break;
			case Instruction::SET: {
				Value a = pop();
				Value b = pop();
				a.ptr_set(b);
				push(a.ptr_get());
				} break;
			case Instruction::CALL: {
				Value v = pop();
				// TODO(bqq): Error handling
				if (v.type == Value::OBJECT) {
					FunctionInstance *fi = v.data.v_inst->cast<FunctionInstance>();
					call_stack.emplace_back(fi);
					for (std::vector<Param>::iterator it = fi->definition->params.begin(); it != fi->definition->params.end(); ++it) {
						call_stack.back().context[it->name] = pop();
					}
					cptr_stack.emplace(pc + 1, end);
					pc = fi->definition->insts.cbegin();
					end = fi->definition->insts.cend();
					goto interp_begin;
				} else if (v.type == Value::DELEGATE) {
					// TODO(bqq): Multiple arguments
					std::vector<Value> w;
					w.push_back(pop());
					push(v.data.v_delegate(w));
				}
				} break;
			case Instruction::POP:
				pop();
				break;
			default:
				// TODO(bqq): Error handling
				break;
			}
			++pc;
		}
		if (call_stack.back().instance)
			call_stack.pop_back();
	}
}

Value Engine::eval(const char* s) {
	Parser p(s);
	Compiler c(func_defs, p.parse_expression());
	if (c.compile()) {
		run(c.get_instructions()); 
		collect_garbage();
		return pop();
	} else
		return Value::Error;
}
Value Engine::eval(const std::vector<Instruction>& i) {
	run(i);
	return pop();
}

Value Engine::call(FunctionInstance* fi, const ParamList& params) {
	call_stack.emplace_back(fi);
	// TODO(bqq): Number of arguments errors
	for (const Value *n = params.begin; n != params.end; n++) {
		call_stack.back().context[fi->definition->params[n - params.begin].name] = *n;
	}
	run(fi->definition->insts);
	return pop();
}
Value& Engine::get_name(const std::string& s) {
	return call_stack.back().context[s];
}

Engine::Call::Call(FunctionInstance *i)
	: instance(i)
{
}

} }