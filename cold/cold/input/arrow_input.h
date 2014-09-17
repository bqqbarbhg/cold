#ifndef _COLD_INPUT_ARROW_INPUT_H
#define _COLD_INPUT_ARROW_INPUT_H

#include <cold/input/input.h>
#include <cold/input/keyboard.h>
#include <glm/glm.hpp>

namespace cold {

// Directional input from some arrow keys
// Usually WASD or arrows
class ArrowInput : public Input<glm::vec2> {
public:
	ArrowInput(SDLKey up, SDLKey down, SDLKey left, SDLKey right)
		: up(up), down(down), left(left), right(right)
	{
	}
	virtual glm::vec2 get() const {
		glm::vec2 v;
		if (Keyboard::down(up)) v.y++;
		if (Keyboard::down(down)) v.y--;
		if (Keyboard::down(left)) v.x--;
		if (Keyboard::down(right)) v.x++;
		if (v.x != 0.0f || v.y != 0.0f)
			return glm::normalize(v);
		return v;
	}
private:
	SDLKey up, down, left, right;
};

};

#endif