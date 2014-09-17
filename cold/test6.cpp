#if 1

#include <cold/script/compile/parse.h>
#include <cold/script/compile/compile.h>
#include <cold/script/engine.h>
#include <cold/script/list.h>
#include <chrono>

void read_line(char* c) {
	while ((*c++ = getchar()) != '\n')
			;
	c[-1] = 0;
}

int main(int argc, char **argv) {
	cold::script::Engine e;
	cold::script::List l = e.create_list();
	l.push(0);
	l.push(1);
	l.push(2);
	l.push(4);
		l.push(0);
	l.push(1);
	l.push(2);
	l.push(4);
		l.push(0);
	l.push(1);
	l.push(2);
	l.push(4);
		l.push(0);
	l.push(1);
	l.push(2);
	l.push(4);
		l.push(0);
	l.push(1);
	l.push(2);
	l.push(4);
		l.push(0);
	l.push(1);
	l.push(2);
	l.push(4);
		l.push(0);
	l.push(1);
	l.push(2);
	l.push(4);
	e.set_global("l", l);
	char buffer[2048];
	while (true) {
		printf("> ");
		read_line(buffer);
		auto _s = std::chrono::high_resolution_clock::now();
		cold::script::Parser p(buffer);
		cold::script::Compiler c(e.get_func_defs(), p.parse_expression());
		if (!c.compile()) {
			std::cout << "err";
			continue;
		}
		auto _m = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; i++) {
			auto v = e.eval(c.get_instructions());
			if (i == 0)
				std::cout << v.repr() << "\n";
			e.collect_garbage();
		}
		auto _e = std::chrono::high_resolution_clock::now();
		std::cout << ((std::chrono::duration_cast<std::chrono::milliseconds>(_e - _m)).count()) << "ms\n";
	}
}

#endif