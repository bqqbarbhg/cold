#if 0

#include <cold/platform/application.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cold/render/impl/gl.h>
#include <cold/render/shader.h>

#include <cold/platform/os.h>
#include <cold/engine/scene.h>
#include <cold/engine/map.h>
#include <cold/engine/block.h>
#include <cold/engine/render/chunk.h>
#include <cold/game/entity/player.h>
#include <cold/input/bind.h>
#include <cold/input/key_input.h>
//#include <cold/input/and_input.h>
#include <cold/resource/text_resource_loader.h>

#undef main
int main(int argc, char** argv) {
	cold::TextResourceLoader trl("data/");
	cold::ResourceLoader::provide(&trl);

	cold::Application app;
	app.create_window(cold::os::get_screen_width(), cold::os::get_screen_height(), 16, cold::Application::WINDOW_NO_BORDER, cold::Application::TOP_LEFT);
	app.set_title("Cold test");
	
	cold::Shader shader;

	shader.compile_file("data\\shader\\test.vert", "data\\shader\\test.frag");
	auto ps = glm::perspective(90.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

	cold::Scene s(new cold::Map(128, 16, 128));
	for (int x = 0; x < 128; x++) {
		for (int z = 0; z < 128; z++) {
			s.map->get_block(x, 0, z)->set_solid(1);
		}
	}

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 2000; i++) {
		s.map->get_block(rand()%128, rand()%16, rand()%128)->set_solid(1);
	}
	
	s.map->get_block(2, 1, 3)->set_solid(1);
	s.map->get_block(2, 1, 4)->set_solid(1);
	s.map->get_block(2, 1, 5)->set_solid(1);
	s.map->get_block(2, 1, 6)->set_solid(1);

	s.add(new cold::EntityPlayer(glm::vec3(5.0f, 5.0f, 5.0f)));
	s.gravity = glm::vec3(0.0f, 0.0f, 0.0f);

	cold::RenderChunk rs(0, 0, 0, 128, 16, 128);
	rs.update(*s.map);

	float time = 0.0f;

	cold::Bind<bool> exit_bind;
	exit_bind += new cold::KeyInput(cold::KeyInput::PRESSED, SDLK_ESCAPE);
	//exit_bind += new cold::AndInput(new cold::KeyInput(cold::KeyInput::DOWN, SDLK_LALT), new cold::KeyInput(cold::KeyInput::PRESSED, SDLK_F4));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	while (app.is_running()) {
		app.poll_events();
		float elapsed = app.update_elapsed();
		if (elapsed > 0.1f)
			continue;
		time += elapsed;

		s.update(elapsed);

		glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		s.camera.update();
		shader.uniforms["WVP"] = s.camera.view_projection;

		s.draw();
		shader.apply();
		rs.draw();

		SDL_GL_SwapBuffers();

		if (exit_bind.get())
			app.quit();
	}

	return 0;
}

#endif