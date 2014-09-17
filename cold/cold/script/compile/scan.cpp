#include "scan.h"

namespace cold { namespace script {

struct kwt {
	const char* name;
	Token tok;
} keywords[] = {
	{ "if", Token::IF },
	{ "then", Token::THEN },
	{ "endif", Token::ENDIF },
	{ "def", Token::DEF },
	{ 0 },
};

Scanner::Scanner(const char* src)
	: ptr(src)
{
}

bool Scanner::get_next_token() {
	char c = *ptr;
	
	// Skip whitespace and comments
	while (true) {
		while (c == ' ' || c == '\t' || c == '\r')
			c = *++ptr;
		if (c == '#') {
			while (c != '\n' && c)
				c = *++ptr;
			continue;
		}
		break;
	}

	// End of file
	if (!c) {
		token.type = Token::EOS;
		return true;
	}

	const char *start = ptr;

	// Identifier
	if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_') {
		c = *++ptr;
		while (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_' || c >= '0' && c <= '9')
			c = *++ptr;

		// Keyword
		for (struct kwt *k = keywords; k->name; k++) {
			if (!std::strncmp(k->name, start, ptr - start) && ptr - start == std::strlen(k->name)) {
				token = k->tok;
				return true;
			}
		}

		token.type = Token::IDENTIFIER;
		token.begin = start;
		token.end = ptr;
		return true;
	}

	// Int constant
	if (c >= '0' && c <= '9') {
		c = *++ptr;
		while (c >= '0' && c <= '9')
			c = *++ptr;
		token.type = Token::INT_CONSTANT;
		token.begin = start;
		token.end = ptr;
		return true;
	}

	ptr++;

	// Operators
	switch (c) {
	case '+': token.type = Token::ADD; return true;
	case '-': token.type = Token::SUB; return true;
	case '*': token.type = Token::MUL; return true;
	case '/': token.type = Token::DIV; return true;
	case '%': token.type = Token::MOD; return true;
	case '=': if (*ptr == '>') {
		ptr++;
		token.type = Token::LAMBDA_ARROW;
	} else token.type = Token::ASSIGN; 
		return true;
	case '(': token.type = Token::OPEN_PAREN; return true;
	case ')': token.type = Token::CLOSE_PAREN; return true;
	case '[': token.type = Token::OPEN_BRACKET; return true;
	case ']': token.type = Token::CLOSE_BRACKET; return true;
	case '\n': token.type = Token::STERM; return true;
	case ',': token.type = Token::COMMA; return true;
	case '?': token.type = Token::QUESTION; return true;
	case ':': token.type = Token::COLON; return true;
	case '.': token.type = Token::DOT; return true;
	}

	return false;
}

} }