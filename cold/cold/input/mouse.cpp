#include "mouse.h"
#include <cold/input/io.h>

namespace cold {

glm::vec2 Mouse::pos;
bool Mouse::lock_updated = false, Mouse::locked = false, Mouse::active = true;
unsigned int Mouse::buttons = 0;
int Mouse::center_x, Mouse::center_y;

void Mouse::set_lock_position(int x, int y) {
	center_x = x;
	center_y = y;
}

void Mouse::set_active(bool a) {
	active = a;
}

void Mouse::_update_position() {
	int x, y;
	buttons = SDL_GetMouseState(&x, &y);
	pos = glm::vec2(x, y);
}

void Mouse::update() {
	if (locked) {
		_update_position();
		if (lock_updated && active) {
			pos -= glm::vec2(center_x, center_y);
			SDL_WarpMouse(center_x, center_y);
		} else {
			pos = glm::vec2(0.0f, 0.0f);
			lock_updated = true;
		}
	} else {
		_update_position();
	}
}

void Mouse::lock() {
	if (locked) return;
	lock_updated = false;
	locked = true;
}

void Mouse::unlock() {
	locked = false;
}

void Mouse::set_visible(bool visible) {
	SDL_ShowCursor(visible);
}

bool Mouse::get_button(int button) {
	return (SDL_BUTTON(button) & buttons) != 0;
}

}