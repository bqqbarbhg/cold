#ifndef _COLD_UTIL_CONFIG_SCANNER_H
#define _COLD_UTIL_CONFIG_SCANNER_H

#include <string>

class BufferedStream;
namespace ConfigScanner {
	struct Token {
		enum Type {
			END_OF_FILE,
			IDENTIFIER,
			ASSIGN,
			STRING,
			NUMBER,
			NEWLINE,
			COMMA,
		};
		Type type;
		long number;
		std::string text;
	};
	bool scan(BufferedStream& stream, Token& token, bool skip_newlines=true);
}

#endif