#ifndef _COLD_SCRIPT_ENGINE_H
#define _COLD_SCRIPT_ENGINE_H

#include <cold/script/value.h>
#include <cold/script/instruction.h>
#include <cold/script/instance.h>
#include <cold/script/object.h>
#include <cold/util/sized_stack.h>
#include <cold/util/assert.h>

#include <stack>
#include <vector>
#include <map>

namespace cold { namespace script {

struct List;
struct FunctionInstance;
struct ParamList;
class Engine {
public:
	Engine(unsigned int stack_size=512);
	~Engine();
	typedef std::map<std::string, Value> Context;
	struct Call {
		Call(FunctionInstance* i);
		FunctionInstance *instance;
		Context context;
	};
	Value get_global(const std::string& name);
	void set_global(const std::string& name, const Value& v);
	Object create_object();
	List create_list();
	Value add_instance(Instance* i);
	Value eval(const char* str);
	Value eval(const std::vector<Instruction>& i);
	Value call(FunctionInstance* fi, const ParamList& params);
	std::vector<FunctionDefinition*>& get_func_defs() { return func_defs; }
	void run(const std::vector<Instruction>& insts);
	void collect_garbage();
private:
	Value& get_name(const std::string& str);
	static void mark_and_push(std::stack<Instance*>& w, const std::map<std::string, Value>& m);
	static void mark_and_push(std::stack<Instance*>& w, const SizedStack<Value>& i);
	void push(const Value& v) { if (stack.push(v)) COLD_ASSERT(0 && "Stack overflow"); }
	Value pop() { return stack.pop(); }
	std::vector<Call> call_stack;
	std::vector<FunctionDefinition*> func_defs;
	SizedStack<Value> stack;
	std::vector<Instance*> instances;
};

} }

#endif