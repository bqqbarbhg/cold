#include "text_resource_parser.h"
#include <cold/resource/load_info.h>

#include <sstream>

namespace cold {

TextResourceParser::TextResourceParser(std::istream& i)
	: stream(i, 64)
{
}

bool TextResourceParser::parse(ResourceLoadInfo& info) {
	using namespace ConfigScanner;
	if (!read_token()) return false;
	while (true) {
		switch (token.type) {
		case Token::IDENTIFIER: {
			std::string k = token.text;
			if (!read_token()) return false;
			if (token.type == Token::ASSIGN) {
				if (!read_token()) return false;
				if (token.type == Token::STRING) {
					info.set_arg(k, token.text);
					if (!read_token()) return false;
				} else
					return false;
			} else {
				info.set_flag(k);
			}
		}
		break;
		case Token::END_OF_FILE:
			return true;
		default:
			return false;
		}
	}
}

bool TextResourceParser::read_token() {
	return ConfigScanner::scan(stream, token);
}

}