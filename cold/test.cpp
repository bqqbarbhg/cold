#if 0
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cold/render/shader.h>
#include <cold/render/types.h>
#include <cold/platform/application.h>
#include <cold/render/vertex_array.h>
#include <cold/render/vertex_buffer.h>
#include <cold/render/vertex_declaration.h>
#include <cold/render/vertex_element.h>
#include <cold/render/index_buffer.h>
#include <cold/render/util/triangle_mesh_builder.h>
#include <cold/render/util/basic_vertex_declarations.h>
#include <cold/render/util/basic_vertex_types.h>
#include <cold/render/mesh.h>

#undef main
int main(int argc, char** argv) {
	using namespace glm;
	cold::Application app;
	app.create_window(800, 600);
	app.set_title("Cold test");
	
	cold::Mesh mesh(cold::VertexPositionColor, cold::DATA_UNSIGNED_INT);
	cold::TriangleMeshBuilder tmb(cold::VertexPositionColor, cold::DATA_UNSIGNED_INT);
	cold::Shader shader;

	shader.compile("data\\shader\\test.vert", "data\\shader\\test.frag");
	auto ps = perspective(90.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

	tmb.add_quad(
		cold::VTPositionColor(-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f),
		cold::VTPositionColor(1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		cold::VTPositionColor(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
		cold::VTPositionColor(1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)
		);

	tmb.apply(mesh);

	float time = 0.0f;

	while (app.is_running()) {
		app.poll_events();
		float elapsed = app.update_elapsed();
		time += elapsed;

		glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader.uniforms["WVP"] = ps * lookAt(vec3(cos(time), 0.0f, sin(time)), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		shader.apply();
		mesh.draw();

		SDL_GL_SwapBuffers();
	}

	return 0;
}
#endif