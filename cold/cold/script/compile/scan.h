#ifndef _COLD_SCRIPT_COMPILE_SCAN_H
#define _COLD_SCRIPT_COMPILE_SCAN_H

#include <cold/script/compile/token.h>
#include <string>

namespace cold { namespace script {

class Scanner {
public:
	Scanner(const char* source);
	bool get_next_token();
	Token token;
private:
	const char* ptr;
};

} }

#endif