#if 0

#include <cold/resource/logging_resource_loader.h>
#include <cold/resource/text_resource_loader.h>
#include <cold/platform/application.h>
#include <cold/render/util/sprite_batch.h>
#include <cold/platform/os.h>
#include <cold/input/bind.h>
#include <cold/input/key_input.h>
#include <cold/render/render.h>
#include <cold/resource/handle.h>
#include <cold/resource/resource_manager.h>

#include <cold/ui/container.h>
#include <cold/ui/panel.h>
#include <cold/ui/label.h>
#include <cold/ui/line_graph.h>
#include <cold/util/string.h>
#include <cold/input/mouse.h>

#include <cold/render/util/line_triangulation.h>

#include <sstream>

#undef main
int main(int argc, char** argv) {
	using namespace cold;
	LoggingResourceLoader r(new TextResourceLoader("data/"), std::cout);
	ResourceLoader::provide(&r);
	Application app;
	app.create_window(800, 600, 16, Application::WINDOW, Application::DEFAULT);
	app.set_title("UI test");
	//music->play();
	SpriteBatch sb(128);
	sb.set_bounds(Rectangle(0, 0, 800.0f, 600.0f));

	cold::Bind<bool> exit_bind;
	exit_bind += new cold::KeyInput(cold::KeyInput::PRESSED, SDLK_ESCAPE);
	//exit_bind += new cold::AndInput(new cold::KeyInput(cold::KeyInput::DOWN, SDLK_LALT), new cold::KeyInput(cold::KeyInput::PRESSED, SDLK_F4));
	cold::Bind<bool> break_bind;
	break_bind += new cold::KeyInput(cold::KeyInput::PRESSED, SDLK_F9);
	ui::Container screen(Rectangle(0, 0, 800.0f, 600.0f));
	UniquePtr<ui::Panel> p = new ui::Panel(Rectangle(10, 10, 100, 50), glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
	ui::LineGraph* lg = new ui::LineGraph(Rectangle(12, 12, 96, 46), glm::vec4(1.0f, 1.0f, 1.0f, 0.2f), ResourceManager<Font>::get("font/ui/mini_outline"), 32, 0.01f);
	ui::Label<const char*>* f = new ui::Label<const char*>(ResourceManager<Font>::get("font/ui/mini_outline"));
	f->bounds.position = glm::vec2(12.0f, 12.0f);
	f->text = "FPS";
	p->add(lg);
	p->add(f);
	UniquePtr<ui::Panel> p2 = new ui::Panel(Rectangle(10, 110 - 40, 100, 50), glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
	ui::LineGraph* lg2 = new ui::LineGraph(Rectangle(12, 112 - 40, 96, 46), glm::vec4(1.0f, 1.0f, 1.0f, 0.2f), ResourceManager<Font>::get("font/ui/mini_outline"), 32, 0.01f);
	ui::Label<const char*>* f2 = new ui::Label<const char*>(ResourceManager<Font>::get("font/ui/mini_outline"));
	f2->bounds.position = glm::vec2(12.0f, 112.0f - 40);
	f2->text = "DRAWCALLS";
	p2->add(lg2);
	p2->add(f2);
	screen.add(p.release());
	screen.add(p2.release());

	glm::vec2 op = glm::vec2(0.0f, 0.0f);
	std::vector<glm::vec2> points;
	float time = 0.0f;
	float t = 0.0f;
	float w = 0.0f;
	int ec = 0;
	float ev = 0.0f;
	unsigned int dc = 0;
	while (app.is_running()) {
		app.poll_events();
		float elapsed = app.update_elapsed();
		time += elapsed;
		t += elapsed;
		render::error_t err;
		ec++;
		ev += elapsed;
		if (t > 0.1f) {
			lg->push(1.0f / (ev / ec));
			lg2->push(dc);
			t = 0.0f;
			ev = 0.0f;
			ec = 0;
		}
		if (render::get_error(err))
			os::message_box("Render Error", render::get_error_string(err).c_str(), os::MBOX_ERROR);
		render::clear(glm::vec4(0.39f, 0.58f, 0.93f, 1.0f));

		if (break_bind.get())
			__debugbreak();

		sb.begin();

		screen.draw(sb);

		if (Mouse::get_button(1)) {
			if (glm::distance(op, Mouse::get_position()) > 5.0f) {
				points.push_back(op = Mouse::get_position());
			}
		}

		sb.end();

		dc = render::draw_calls;
		render::update();
	}
}

#endif