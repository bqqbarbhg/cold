#include "compile.h"
#include "ast.h"
#include <cold/script/instruction.h>
#include <cold/script/function_definition.h>

namespace cold { namespace script {

void Compiler::push_inst(const Instruction& i) {
	insts.push_back(i);
}
void Compiler::push_func_def(const FunctionDefinition& f) {
	function_defs.push_back(new FunctionDefinition(f));
}

Compiler::Compiler(std::vector<FunctionDefinition*>& fns, AstNode* n)
	: function_defs(fns), node(n), err_node(NULL)
{
}
Compiler::~Compiler() {
	delete node;
}

bool Compiler::compile(AstNode* n) {
	if (!n) {
		error = PARSE_ERROR;
		return false;
	}
	return !n->emit(*this);
}

bool Compiler::compile(){
	return compile(node);
}

const std::vector<Instruction>& Compiler::get_instructions() {
	return insts;
}
std::vector<FunctionDefinition*>& Compiler::get_function_defs() {
	return function_defs;
}

bool AstNode::emit_lvalue(Compiler &c) const {
	c.err_node = this;
	c.error = Compiler::NOT_RVALUE;
	return false;
}

bool AstStatementList::emit(Compiler& c) const {
	for (std::vector<AstNode*>::const_iterator it = nodes.cbegin(); it != nodes.cend(); ++it) {
		if ((*it)->emit(c)) return true;
		c.push_inst(Instruction::make_pop());
	}
	return false;
}

bool AstAssign::emit(Compiler& c) const {
	if (src->emit(c)) return true;
	if (dst->emit_lvalue(c)) return true;
	c.push_inst(Instruction::make_set());
	return false;
}

bool AstIdentifier::emit(Compiler& c) const {
	c.push_inst(Instruction::make_get(name.c_str(), Instruction::GET_NAME));
	return false;
}
bool AstIdentifier::emit_lvalue(Compiler &c) const {
	c.push_inst(Instruction::make_get(name.c_str(), Instruction::GET_NAME_REF));
	return false;
}

bool AstCall::emit(Compiler& c) const {
	for (std::vector<AstNode*>::const_reverse_iterator cri = params.crbegin(); cri != params.crend(); ++cri) {
		(*cri)->emit(c);
	}
	node->emit(c);
	c.push_inst(Instruction::make_call());
	return false;
}

bool AstConstant::emit(Compiler& c) const {
	switch (type) {
	case INT:
		c.push_inst(Instruction::make_const(value._int));
		break;
	}
	return false;
}

bool AstBinOp::emit(Compiler& c) const {
	if (left->emit(c)) return true;
	if (right->emit(c)) return true;

	char op;
	switch (type) {
	case Token::ADD: op = '+'; break;
	case Token::SUB: op = '-'; break;
	case Token::MUL: op = '*'; break;
	case Token::DIV: op = '/'; break;
	case Token::MOD: op = '%'; break;
	default:
		c.error = Compiler::UNSUPPORTED_OP;
		c.err_node = this;
		return true;
	}
	c.push_inst(Instruction::make_op(op));
	return false;
}

bool AstUnaryOp::emit(Compiler& c) const {
	if (node->emit(c)) return true;

	char op;
	switch (type) {
	case Token::ADD: op = 'p'; break;
	case Token::SUB: op = 'n'; break;
	}
	c.push_inst(Instruction::make_op(op));
	return false;
}

bool AstTernaryOp::emit(Compiler& c) const {
	c.error = Compiler::INTERNAL_ERROR;
	c.err_node = this;
	return true;
}
bool AstTernaryOp::emit_lvalue(Compiler& c) const {
	c.error = Compiler::INTERNAL_ERROR;
	c.err_node = this;
	return true;
}

bool AstMember::emit(Compiler& c) const {
	if (node->emit(c)) return true;
	c.push_inst(Instruction::make_get(name.c_str(), Instruction::GET_MEMBER));
	return false;
}
bool AstMember::emit_lvalue(Compiler& c) const {
	if (node->emit(c)) return true;
	c.push_inst(Instruction::make_get(name.c_str(), Instruction::GET_MEMBER_REF));
	return false;
}

bool AstLambda::emit(Compiler& c) const {
	Compiler i(c.get_function_defs());
	if (!i.compile(body)) {
		c.error = i.error;
		c.err_node = i.err_node;
		return true;
	}
	FunctionDefinition fd(i.get_instructions(), params);
	std::vector<FunctionDefinition*>& f = c.get_function_defs();
	for (unsigned int i = 0; i != f.size(); i++) {
		if (*f[i] == fd) {
			c.push_inst(Instruction::make_func(i));
			return false;
		}
	}
	c.push_func_def(fd);
	c.push_inst(Instruction::make_func((unsigned int)f.size() - 1));
	return false;
}

bool AstTuple::emit(Compiler& c) const {
	if (nodes.size() == 1) {
		nodes[0]->emit(c);
		return false;
	}
	// TODO(bqq): Tuples
	c.error = Compiler::INTERNAL_ERROR;
	c.err_node = this;
	return true;
}

} }