#include "parse.h"

#include <cold/script/compile/ast.h>

namespace cold { namespace script {

namespace {
	void delete_vector(std::vector<AstNode*> vec) {
		for (std::vector<AstNode*>::iterator it = vec.begin(); it != vec.end(); ++it)
			delete *it;
	}
}

Parser::Parser(const char* src)
	: scanner(src), error(NONE)
{
}

AstNode* Parser::scan_error() {
	error = SCAN_ERROR;
	return NULL;
}

const char* Parser::get_error_type_string(Error err) {
	switch(err) {
		case NONE: return "none";
		case SCAN_ERROR: return "scan error";
		case UNEXPECTED_SYMBOL: return "unexpected symbol";
		case CLOSE_PAREN_EXPECTED: return "expected ')'";
		case ATTRIBUTE_EXPECTED: return "expected an attribute";
		case SYNTAX_ERROR: return "syntax error";
		case UNKNOWN_OPERATOR: return "unknown operator";
		case UNKNOWN_TOKEN: return "unknown token";
		case COLON_EXPECTED: return "expected ':'";
		case CLOSE_BRACKET_EXPECTED: return "expected ']'";
		case INTERNAL_ERROR: return "internal error";
		case EXPECTED_LAMBDA_ARROW: return "expected '=>'";
		case EXPECTED_PARAMETER: return "expected parameter";
		case EXPECTED_END_OF_FILE: return "expected end of file";
	}
	return "error string error";
}

std::string Parser::get_error_string() const {
	switch (error) {
	case NONE: return "";
	case UNEXPECTED_SYMBOL:
	case UNEXPECTED_OPERATOR:
	case UNKNOWN_TOKEN:
	case UNKNOWN_OPERATOR:
		return std::string("unexpected ") + scanner.token.get_name();
	}
	return std::string(get_error_type_string(error));
}

Parser::Error Parser::get_error() const {
	return error;
}

bool Parser::accept(Token::Type t) {
	if (error != NONE) return false;
	if (scanner.token.type == t) {
		if (!scanner.get_next_token()) {
			error = SCAN_ERROR;
			return false;
		}
		return true;
	}
	return false;
}

bool Parser::require(Token::Type t) {
	if (scanner.token.type == t) {
		if (!scanner.get_next_token()) {
			error = SCAN_ERROR;
			return true;
		}
		return false;
	}
	return true;
}

AstNode* Parser::nud(const Token& t) {
	AstNode* node;
	switch (t.type) {
	case Token::IDENTIFIER:
		return new AstIdentifier(std::string(t.begin, t.end - t.begin));
	case Token::INT_CONSTANT:
		return new AstConstant(AstConstant::INT, t.begin, t.end);
	case Token::ADD:
	case Token::SUB:
		node = expression(100);
		if (!node) return NULL;
		return new AstUnaryOp(t.type, node);
	case Token::OPEN_PAREN: {
		std::vector<AstNode*> tuple_vec;

		if (accept(Token::CLOSE_PAREN)) {
			return new AstTuple(std::vector<AstNode*>());
		}
		do {
			node = expression();
			if (!node) return NULL;
			tuple_vec.push_back(node);
		} while (accept(Token::COMMA));
		if (require(Token::CLOSE_PAREN)) {
			if (error == NONE)
				error = CLOSE_PAREN_EXPECTED;
			delete node;
			return NULL;
		}
		return new AstTuple(tuple_vec);
		}
	}
	error = UNKNOWN_TOKEN;
	return NULL;
}

AstNode* Parser::led(const Token& t, AstNode* o) {
	AstNode* node;
	switch (t.type) {
	case Token::ADD:
	case Token::SUB:
	case Token::MUL:
	case Token::DIV:
	case Token::MOD:
		node = expression(lbp(t.type));
		if (!node) return NULL;
		return new AstBinOp(t.type, o, node);
	case Token::ASSIGN:
		node = expression(lbp(t.type) - 1);
		if (!node) return NULL;
		return new AstAssign(o, node);
	case Token::QUESTION: {
		node = expression();
		if (!node) return NULL;
		if (require(Token::COLON)) {
			if (error == NONE)
				error = COLON_EXPECTED;
			delete node;
			return NULL;
		}
		AstNode* node2 = expression();
		if (!node2) {
			delete node;
			return NULL;
		}
		return new AstTernaryOp(o, node, node2);
		} break;
	case Token::OPEN_PAREN: {
		std::vector<AstNode*> params;
		if (scanner.token.type != Token::CLOSE_PAREN) {
			while (true) {
				node = expression();
				if (!node) {
					delete_vector(params);
					return NULL;
				}
				params.push_back(node);
				if (scanner.token.type != Token::COMMA) {
					break;
				}
				if (require(Token::COMMA)) {
					error = INTERNAL_ERROR;
					delete_vector(params);
					return NULL;
				}
			}
		}
		if (require(Token::CLOSE_PAREN)) {
			error = CLOSE_PAREN_EXPECTED;
			delete_vector(params);
			return NULL;
		}
		return new AstCall(o, params);
	} break;
	case Token::OPEN_BRACKET:
		node = expression();
		if (!node) return NULL;
		if (require(Token::CLOSE_BRACKET)) {
			if (error == NONE)
				error = CLOSE_BRACKET_EXPECTED;
			delete node;
			return NULL;
		}
		return new AstBinOp(Token::OPEN_BRACKET, o, node);
	case Token::DOT:
		if (scanner.token.type != Token::IDENTIFIER) {
			if (error == NONE)
				error = ATTRIBUTE_EXPECTED;
			return NULL;
		}
		node = new AstMember(o, std::string(scanner.token.begin, scanner.token.end));
		if (!scanner.get_next_token()) {
			error = SCAN_ERROR;
			delete node;
			return NULL;
		}
		return node;
	case Token::LAMBDA_ARROW: {
		Param p;
		std::vector<Param> vec;
		if (o->get_params(vec)) return NULL;
		node = expression(lbp(Token::LAMBDA_ARROW) - 1);
		if (!node) return NULL;
		delete o;
		return new AstLambda(vec, node);
		}
	}
	if (t.is_operator()) {
		error = UNEXPECTED_OPERATOR;
		return NULL;
	}
	error = UNKNOWN_OPERATOR;
	return NULL;

}

unsigned int Parser::lbp(Token::Type t) {
	switch (t) {
	case Token::IDENTIFIER:
	case Token::INT_CONSTANT:
	case Token::EOS:
	case Token::CLOSE_PAREN:
	case Token::CLOSE_BRACKET:
	case Token::COMMA:
	case Token::COLON:
		return 0;
	case Token::ASSIGN:
		return 10;
	case Token::LAMBDA_ARROW:
		return 15;
	case Token::QUESTION:
		return 20;
	case Token::ADD:
	case Token::SUB:
		return 110;
	case Token::MUL:
	case Token::DIV:
	case Token::MOD:
		return 120;
	case Token::OPEN_PAREN:
	case Token::OPEN_BRACKET:
	case Token::DOT:
		return 150;
	}
	throw "Unknown token";
}

AstNode* Parser::expression(unsigned int rpb) {
	Token t = scanner.token;
	if (!scanner.get_next_token()) return scan_error();
	AstNode *left = nud(t);
	if (!left) {
		delete left;
		return NULL;
	}
	while (rpb < lbp(scanner.token.type)) {
		t = scanner.token;
		if (!scanner.get_next_token()) {
			delete left;
			return scan_error();
		}
		AstNode *n = led(t, left);
		if (!n) {
			delete left;
			return NULL;
		} else
			left = n;
	}
	return left;
}

bool Parser::param_expression(Param& param) {
	const char *b = scanner.token.begin,
	           *e = scanner.token.end;
	if (accept(Token::IDENTIFIER)) {
		param.name = std::string(b, e);
		error = EXPECTED_PARAMETER;
		return false;
	}
	return true;
}

AstNode* Parser::parse_expression() {
	if (!scanner.get_next_token()) {
		error = SCAN_ERROR;
		return NULL;
	}
	AstNode* n =  expression();
	if (!n) return NULL;
	if (require(Token::EOS)) {
		error = scanner.token.is_operator() ? UNEXPECTED_OPERATOR : UNEXPECTED_SYMBOL;
		delete n;
		return NULL;
	}
	return n;
}

} }