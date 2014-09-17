#if 0
#include <cstdio>
#include <cold/script/compile/parse.h>
#include <cold/script/compile/ast.h>

int main(int argc, char** argv) {
	char buffer[2048];
	char *cptr;
	while (true) {
		cptr = buffer;
		printf("> ");
		while ((*cptr++ = getchar()) != '\n')
			;
		cptr[-1] = 0;
		cold::script::Parser parser(buffer);
		cold::script::AstNode* n = parser.parse_expression();
		if (n) {
			printf("%s\n", n->repr().c_str());
			delete n;
		} else {
			printf("%s\n", parser.get_error_string().c_str());
		}
	}
}

#endif