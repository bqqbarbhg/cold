#include "token.h"
#include <cold/util/assert.h>

namespace cold { namespace script {

bool Token::is_operator() const {
	switch (type) {
		case ADD:
		case SUB:
		case MUL:
		case DIV:
		case MOD:
		case ASSIGN:
		case DOT:
		case QUESTION:
		case COLON:
		case LAMBDA_ARROW:
			return true;
		default: return false;
	}
}
const char* Token::get_name() const {
	switch (type) {
		case IDENTIFIER: return "identifier";
		case INT_CONSTANT: return "integer";
		case ADD: return "'+'";
		case SUB: return "'-'";
		case MUL: return "'*'";
		case DIV: return "'/'";
		case MOD: return "'%'";
		case ASSIGN: return "'='";
		case DOT: return "'.'";
		case QUESTION: return "'?'";
		case COLON: return "':'";
		case OPEN_PAREN: return "'('";
		case CLOSE_PAREN: return "')'";
		case OPEN_BRACKET: return "'['";
		case CLOSE_BRACKET: return "']'";
		case STERM: return "';'";
		case EOS: return "end of file";
		case IF: return "if";
		case COMMA: return ",";
		case LAMBDA_ARROW: return "=>";
	}
	COLD_ASSERT(false);
	return 0;
}

} }