#ifndef _COLD_SCRIPT_INSTRUCTION_H
#define _COLD_SCRIPT_INSTRUCTION_H

namespace cold { namespace script {

struct FunctionDefinition;
struct Instruction {
	enum Type {
		INT_CONST,
		OP,
		POP,
		GET_NAME,
		GET_NAME_REF,
		GET_MEMBER,
		GET_MEMBER_REF,
		SET,
		CALL,
		FUNCTION,
	};
	Instruction(Type t);
	Instruction(const Instruction& i);
	~Instruction();
	Instruction& operator=(Instruction i);
	bool operator==(const Instruction& rhs) const;
	bool operator!=(const Instruction& rhs) const;
	static Instruction make_pop();
	static Instruction make_const(int c);
	static Instruction make_op(char op);
	static Instruction make_get(const char* n, Type t);
	static Instruction make_set();
	static Instruction make_call();
	static Instruction make_func(unsigned int fi);
	Type type;
	union {
		int v_int;
		char op;
		char* name;
		unsigned int func;
	} data;
};

} }

#endif