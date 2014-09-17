#ifndef _COLD_SCRIPT_FUNCTION_DEFINITION_H
#define _COLD_SCRIPT_FUNCTION_DEFINITION_H

#include <vector>
#include <string>
#include <cold/script/instruction.h>
#include <cold/script/param.h>

namespace cold { namespace script {

struct FunctionDefinition {
	FunctionDefinition(const std::vector<Instruction>& i, const std::vector<Param>& p);

	bool operator==(const FunctionDefinition& fd) const;
	bool operator!=(const FunctionDefinition& fd) const;
	void update_hash();
	std::string repr() const;
	std::vector<Instruction> insts;
	std::vector<Param> params;
	unsigned int hash;
};

} }

#endif