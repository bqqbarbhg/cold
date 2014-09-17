#ifndef _COLD_SCRIPT_COMPILE_TOKEN_H
#define _COLD_SCRIPT_COMPILE_TOKEN_H

namespace cold { namespace script {

struct Token {
enum Type {
	IDENTIFIER,
	NUMBER,
	OPEN_PAREN,
	CLOSE_PAREN,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	IF,
	THEN,
	ENDIF,
	DEF,
	ASSIGN,
	STERM,
	COMMA,
	INT_CONSTANT,
	DOT,
	QUESTION,
	COLON,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	EOS,
	LAMBDA_ARROW,
} type;
bool is_operator() const;
const char* get_name() const;
const char *begin, *end;
};

} }

#endif