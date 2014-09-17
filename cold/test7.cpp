#if 0

#include <cold/platform/application.h>
#include <cold/resource/text_resource_loader.h>
#include <cold/resource/logging_resource_loader.h>
#include <cold/resource/load_info.h>
#include <cold/resource/resource_manager.h>
#include <cold/render/shader.h>
#include <cold/render/util/sprite_batch.h>
#include <cold/input/bind.h>
#include <cold/input/key_input.h>
#include <cold/input/and_input.h>
#include <cold/render/render.h>
#include <cold/platform/os.h>
#include <cold/render/texture.h>
#include <cold/math/rectangle.h>
#include <cold/render/font.h>
#include <cold/audio/audio.h>
#include <cold/audio/music.h>
#include <cold/resource/file_handle.h>
#include <cold/audio/sound.h>
#include <cold/audio/sound_manager.h>
#include <SDL_mixer.h>

#undef main
int main(int argc, char** argv) {
	using namespace cold;
	audio::initialize();
	audio::SoundManager::set_channels(32);

	LoggingResourceLoader r(new TextResourceLoader("data/"), std::cout);
	ResourceLoader::provide(&r);
	Application app;
	app.create_window(os::get_screen_width(), os::get_screen_height(), 16, Application::WINDOW, Application::DEFAULT);
	app.set_title("Resource test");
	Handle<Texture> cat = ResourceManager<Texture>::get("texture/cat");
	Handle<Font> font = ResourceManager<Font>::get("font/pfwd");
	Handle<Music> music = ResourceManager<Music>::get("music/apta");
	Handle<Sound> sound = ResourceManager<Sound>::get("sound/hit");
	//music->play();
	SpriteBatch sb(128);
	sb.set_bounds(Rectangle(0, 0, (float)os::get_screen_width(), (float)os::get_screen_height()));

	Keyboard::begin_read(200, 20);

	cold::Bind<bool> exit_bind;
	exit_bind += new cold::KeyInput(cold::KeyInput::PRESSED, SDLK_ESCAPE);
	exit_bind += new cold::AndInput(new cold::KeyInput(cold::KeyInput::DOWN, SDLK_LALT), new cold::KeyInput(cold::KeyInput::PRESSED, SDLK_F4));
	float time = 0.0f;
	st_string_utf8 str, gstr;
	while (app.is_running()) {
		app.poll_events();
		float elapsed = app.update_elapsed();
		time += elapsed;
		render::error_t err;
		if (render::get_error(err))
			os::message_box("Render Error", render::get_error_string(err).c_str(), os::MBOX_ERROR);
		render::clear(glm::vec4(0.39f, 0.58f, 0.93f, 1.0f));

		sb.begin(BlendState::AlphaBlend);

		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				sb.draw(
					cat,
					glm::vec2(x * cat->get_width() - time, y * cat->get_height()),
					glm::vec4(0.5f + 0.5f * glm::sin(time * 2.0f + (x ^ y) * x - y), 0.5f + 0.5f * glm::sin(time * 3.0f + (x ^ y) * x - y), 0.5f + 0.5f * glm::sin(time * 5.0f + (x ^ y) * x - y), 1.0f),
					glm::vec2(glm::sin(time * 4.0f + (float)(x ^ y) - 3.14159f)),
					time,
					glm::vec2(0.5f, 0.5f),
					Rectangle(0.25f + glm::sin(time * 4.0f + (float)(x ^ y)) * 0.25f, 0.0f, 0.5f, 1.0f));
			}
		}
		auto ga = L"ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ αβγδεζηθικλμνξοπρςστυφχψω";
		auto fa = L"ABGDEZHFIKLMNXOPRSTGFCZÅ abgdezhfiklmnxoprqstgfczå";
		while (st_char c = Keyboard::read()) {
			//sound->play(audio::MEDIUM);
			//str += c;
			if (c == 8) {
				if (!str.empty())
					str.erase(str.end() - 1);
				else
					sound->play(audio::MEDIUM);
				break;
			}
			bool f = true;
			for (auto gg = ga, ff = fa; gg < ga + 51; gg++, ff++) {
				if (c == *ff) {
					str += *gg;
					f = false;
					break;
				}
			}
			if (f)
				str += c;
			//
		}
		sb.draw_string(font, fmod(time, 0.5f) < 0.25f ? str + L'|' : str, glm::vec2(10.0f, 10.0f));

		sb.end();

		render::update();
	}
}

#endif