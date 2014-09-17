#if 0

#include <glm/glm.hpp>

#include <cold/platform/application.h>
#include <cold/input/bind.h>
#include <cold/input/key_input.h>
#include <cold/render/impl/gl.h>
#include <cold/ui/container.h>
#include <cold/ui/panel.h>
#include <cold/ui/ui.h>
#include <cold/platform/os.h>
#include <cold/render/render.h>

#undef main
int main(int argc, char** argv) {
	using namespace cold;
	using namespace glm;
	
	// Create the application
	Application app;
	if (!app.create_window(800, 600, Application::WINDOW, Application::DEFAULT)) return 1;
	app.set_title("UI Test");
	ui::initialize();
	 
	// Allow exit
	Bind<bool> exit_bind;
	exit_bind += new KeyInput(KeyInput::PRESSED, SDLK_ESCAPE);

	// Create test UI
	ui::Container screen;
	screen.set_bounds(cold::Rectangle(0, 0, 1, 1));
	ui::Panel *test_panel = new ui::Panel();
	test_panel->set_bounds(cold::Rectangle(0, 0, 1, 1));
	test_panel->set_color(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	screen.add(test_panel);

	// Main loop
	while (app.is_running()) {
		app.poll_events();

		if (exit_bind.get())
			app.quit();

		if (render::error_t err = render::get_error(err)) {
			os::message_box("Render error", render::get_error_string(err).c_str(), os::MBOX_ERROR);
		}

		render::clear(glm::vec4(0.39f, 0.58f, 0.93f, 1.0f));

		screen.draw();

		render::update();
	}

	return 0;
}

#endif