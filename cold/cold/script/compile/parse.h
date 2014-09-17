#ifndef _COLD_SCRIPT_COMPILE_PARSE_H
#define _COLD_SCRIPT_COMPILE_PARSE_H
#include <cold/script/compile/token.h>
#include <cold/script/compile/scan.h>

namespace cold { namespace script {

struct AstNode;
struct Param;
class Parser {
public:
	enum Error {
		NONE,
		SCAN_ERROR,
		UNEXPECTED_SYMBOL,
		CLOSE_PAREN_EXPECTED,
		SYNTAX_ERROR,
		UNKNOWN_OPERATOR,
		UNKNOWN_TOKEN,
		COLON_EXPECTED,
		CLOSE_BRACKET_EXPECTED,
		UNEXPECTED_OPERATOR,
		EXPECTED_PARAMETER,
		EXPECTED_LAMBDA_ARROW,
		ATTRIBUTE_EXPECTED,
		EXPECTED_END_OF_FILE,
		INTERNAL_ERROR,
	};
	Parser(const char* src);
	AstNode* parse_expression();
	AstNode* parse_statements();
	Error get_error() const;
	std::string get_error_string() const;
	static const char* get_error_type_string(Error err);
private:
	AstNode* expression(unsigned int rbp=0);
	bool param_expression(Param& param);
	AstNode* nud(const Token& t);
	AstNode* led(const Token& t, AstNode* o);
	unsigned int lbp(Token::Type t);
	AstNode* scan_error();
	bool require(Token::Type t);
	bool accept(Token::Type t);
	Scanner scanner;
	Error error;
	std::string error_str;
};

} }

#endif