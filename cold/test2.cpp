#if 0
#include <cstdio>
#include <cold/render/shader.h>
#include <cold/platform/application.h>

#define PRINT_INT(expr) printf(#expr " = %d\n", expr);

void asd(const cold::Shader& s) {
	glm::vec2 c = s.uniforms.find("ebin")->second;
}

int main(int argc, char** argv) {
	cold::Application a;
	a.create_window(800, 600);
	cold::Shader s;
	s.uniforms["ebin"] = 2.0f;
	asd(s);
	getchar();
}
#endif