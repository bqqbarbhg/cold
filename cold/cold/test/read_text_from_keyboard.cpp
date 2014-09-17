#include <cold/game/game.h>
#include <cold/input/keyboard.h>
#include <cold/util/string.h>
#include <cold/render/util/sprite_batch.h>
#include <cold/resource/handle.h>
#include <cold/resource/resource_manager.h>
#include <cold/render/font.h>
using namespace cold;
using namespace glm;

/*class Game : public game::Game {
	st_string string = "";
	SpriteBatch batch = SpriteBatch(256);
	Handle<Font> font;

	void initialize()
	{
		font = ResourceManager<Font>::get("test_font");
		Keyboard::begin_read();
	}
	void uninitialize()
	{
		Keyboard::end_read();
	}
	void update(float elapsed)
	{
		while (st_char ch = Keyboard::read()) {
			string += ch;
		}
	}
	void draw()
	{
		batch.begin();
		batch.draw_string(font, string, vec2(10.0f, 10.0f));
		batch.end();
	}
};*/