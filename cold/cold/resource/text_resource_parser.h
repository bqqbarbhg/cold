#ifndef _COLD_RESOURCE_TEXT_RESOURCE_PARSER_H
#define _COLD_RESOURCE_TEXT_RESOURCE_PARSER_H

#include <iostream>
#include <cold/util/buffered_stream.h>
#include <cold/util/config_scanner.h>

namespace cold {

struct ResourceLoadInfo;
class TextResourceParser {
public:
	TextResourceParser(std::istream& i);
	bool parse(ResourceLoadInfo& info);
private:
	bool read_token();
	ConfigScanner::Token token;
	BufferedStream stream;
};

}

#endif