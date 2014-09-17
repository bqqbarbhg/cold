#ifndef _COLD_SCRIPT_COMPILE_COMPILE_H
#define _COLD_SCRIPT_COMPILE_COMPILE_H

#include <cold/script/instruction.h>

#include <vector>

namespace cold { namespace script {

struct AstNode;
class Compiler {
public:
	enum Error {
		NONE,
		NOT_RVALUE,
		UNSUPPORTED_OP,
		INTERNAL_ERROR,
		PARSE_ERROR,
	};
	
	Compiler(std::vector<FunctionDefinition*>& defs, AstNode* n=0);
	~Compiler();

	bool compile();
	bool compile(AstNode* node);

	void push_inst(const Instruction& i);
	void push_func_def(const FunctionDefinition& f);
	const std::vector<Instruction>& get_instructions();
	std::vector<FunctionDefinition*>& get_function_defs();

	Error error;
	const AstNode *err_node;

private:
	AstNode *node;
	std::vector<Instruction> insts;
	std::vector<FunctionDefinition*>& function_defs; 
};

} }

#endif