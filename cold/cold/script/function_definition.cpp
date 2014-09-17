#include "function_definition.h"

#include <iostream>
#include <sstream>
#include <functional>

namespace std {
template <> struct hash<cold::script::Param> {
	size_t operator()(const cold::script::Param& p) const {
		return p.flags + std::hash<std::string>()(p.name);
	}
};
template <> struct hash<cold::script::Instruction> {
	size_t operator()(const cold::script::Instruction& i) const {
		using namespace cold::script;
		switch (i.type) {
			case Instruction::INT_CONST:
				return i.data.v_int;
			case Instruction::GET_NAME:
			case Instruction::GET_NAME_REF:
			case Instruction::GET_MEMBER:
			case Instruction::GET_MEMBER_REF:
				return std::hash<std::string>()(i.data.name);
			case Instruction::FUNCTION:
				return (size_t)i.data.func ^ 0xCDEF;
			case Instruction::OP:
				return (size_t)i.data.op ^ 0x1234;
			default:
				return i.type;
		}
	}
};
}
namespace {
template <typename T> std::size_t vector_hash(const std::vector<T>& vt) {
	size_t hash = 0;
	for (std::vector<T>::const_iterator it = vt.cbegin(); it != vt.cend(); ++it) {
		hash = hash * 17 + std::hash<T>()(*it);
	}
	return hash;
}
}
namespace cold { namespace script {

FunctionDefinition::FunctionDefinition(const std::vector<Instruction>& i, const std::vector<Param>& p)
	: insts(i), params(p)
{
	update_hash();
}

void FunctionDefinition::update_hash() {
	hash
		= vector_hash(params)
		+ vector_hash(insts);
}

bool FunctionDefinition::operator==(const FunctionDefinition& fd) const {
	if (hash != fd.hash) return false;
	if (insts != fd.insts) return false;
	if (params != fd.params) return false;
	return true;
}
bool FunctionDefinition::operator!=(const FunctionDefinition& fd) const {
	return !(*this == fd);
}

std::string FunctionDefinition::repr() const {
	std::stringstream s(std::ios::out);
	s << "(";
	for (std::vector<Param>::const_iterator it = params.cbegin(); it != params.cend(); ++it) {
		s << it->repr();
		if (it + 1 < params.cend())
			s << ", ";
	}
	s << ") => (...)";
	return s.str();
}

} }