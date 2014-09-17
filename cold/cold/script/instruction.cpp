#include "instruction.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cold/script/function_definition.h>

namespace cold { namespace script {

Instruction::Instruction(Type t)
	: type(t)
{
}

Instruction::Instruction(const Instruction& i)
	: type(i.type)
{
	if (type == GET_NAME || type == GET_NAME_REF || type == GET_MEMBER || type == GET_MEMBER_REF) {
		std::size_t w = std::strlen(i.data.name) + 1;
		data.name = (char*)std::malloc(w);
		std::memcpy(data.name, i.data.name, w);
	} else if (type == INT_CONST) {
		data.v_int = i.data.v_int;
	} else if (type == OP) {
		data.op = i.data.op;
	} else if (type == FUNCTION) {
		data.func = i.data.func;
	}
}
Instruction::~Instruction() {
	if (type == GET_NAME || type == GET_NAME_REF || type == GET_MEMBER || type == GET_MEMBER_REF) {
		std::free(data.name);
	}
}
Instruction& Instruction::operator=(Instruction i) {
	std::swap(*this, i);
	return *this;
}

bool Instruction::operator==(const Instruction& rhs) const {
	if (type != rhs.type) return false;
	switch (type) {
		case INT_CONST:
			return data.v_int == rhs.data.v_int;
		case GET_NAME:
		case GET_NAME_REF:
		case GET_MEMBER:
		case GET_MEMBER_REF:
			return !std::strcmp(data.name, rhs.data.name);
		case FUNCTION:
			return data.func == rhs.data.func;
		case OP:
			return data.op == rhs.data.op;
		default:
			return true;
	}
}
bool Instruction::operator!=(const Instruction& rhs) const {
	return !(*this == rhs);
}

Instruction Instruction::make_pop() {
	return Instruction(POP);
}
Instruction Instruction::make_set() {
	return Instruction(SET);
}
Instruction Instruction::make_call() {
	return Instruction(CALL);
}
Instruction Instruction::make_op(char op) {
	Instruction i(OP);
	i.data.op = op;
	return i;
}
Instruction Instruction::make_const(int c) {
	Instruction i(INT_CONST);
	i.data.v_int = c;
	return i;
}
Instruction Instruction::make_get(const char* s, Type t) {
	Instruction i(t);
	std::size_t w = std::strlen(s) + 1;
	i.data.name = (char*)std::malloc(w);
	std::memcpy(i.data.name, s, w);
	return i;
}
Instruction Instruction::make_func(unsigned int id) {
	Instruction i(FUNCTION);
	i.data.func = id;
	return i;
}


} }