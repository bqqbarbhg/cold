#include "config_scanner.h"
#include <cold/util/buffered_stream.h>
#include <iostream>
#include <sstream>

bool ConfigScanner::scan(BufferedStream& stream, Token& token, bool skw) {
	char c = stream.peek();
	while (true) {
		while (c == ' ' || c == '\t' || c == '\r' || (c == '\n' && skw))
			c = stream.get();
		break;
	}
	
	if (!c) {
		token.type = Token::END_OF_FILE;
		return true;
	}

	if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_') {
		std::ostringstream os;
		do {
			os << c;
			c = stream.get();
		} while (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_' || c == '-');

		token.type = Token::IDENTIFIER;
		token.text = os.str();
		return true;
	}

	if (c >= '0' && c <= '9' || c == '-') {
		long val = 0;
		bool neg = false;
		if (c == '-') {
			c = stream.get();
			if (c < '0' || c > '9')
				return false;
			neg = true;
		} 
		val = c - '0';
		c = stream.get();
		while (c >= '0' && c <= '9') {
			val = val * 10 + (c - '0');
			c = stream.get();
		}
		token.type = Token::NUMBER;
		token.number = neg ? -val : val;
		return true;
	}

	if (c == '"') {
		std::ostringstream os;
		c = stream.get();
		while (c != '"') {
			if (!c) return false;
			os << c;
			c = stream.get();
		} while (c != '"');
		stream.get();
		token.type = Token::STRING;
		token.text = os.str();
		return true;
	}

	stream.get();
	switch (c) {
	case '=': token.type = Token::ASSIGN; return true;
	case '\n': token.type = Token::NEWLINE; return true;
	case ',': token.type = Token::COMMA; return true;
	}
	return false;
}