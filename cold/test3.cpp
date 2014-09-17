#if 0

#include <cold/platform/application.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cold/render/impl/gl.h>
#include <cold/render/shader.h>

#include <cold/engine/map.h>
#include <cold/engine/block.h>
#include <cold/engine/render/chunk.h>

#undef main
int main(int argc, char** argv) {
	cold::Application app;
	app.create_window(800, 600);
	app.set_title("Cold test");
	
	cold::Shader shader;

	shader.compile("data\\shader\\test.vert", "data\\shader\\test.frag");
	auto ps = glm::perspective(90.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

	cold::Map map(16, 16, 16);
	map.get_block(5, 5, 5)->set_solid(0);
	map.get_block(4, 5, 5)->set_solid(0);
	map.get_block(3, 5, 5)->set_solid(0);
	map.get_block(5, 6, 5)->set_solid(0);
	map.get_block(5, 7, 5)->set_solid(0);

	cold::RenderChunk rs(0, 0, 0, 16, 16, 16);
	rs.update(map);

	float time = 0.0f;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	while (app.is_running()) {
		app.poll_events();
		float elapsed = app.update_elapsed();
		time += elapsed;

		glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.uniforms["WVP"] = ps * glm::lookAt(glm::vec3(cos(time), 0.7f, glm::sin(time)) * 10.0f, glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		shader.apply();
		rs.draw();

		SDL_GL_SwapBuffers();
	}

	return 0;
}

#endif