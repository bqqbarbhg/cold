#ifndef _COLD_INPUT_MOUSE_INPUT_H
#define _COLD_INPUT_MOUSE_INPUT_H

#include <cold/input/input.h>
#include <cold/input/mouse.h>
#include <glm/glm.hpp>

namespace cold {

// Returns input from the mouse movement
class MouseInput : public Input<glm::vec2> {
public:
	glm::vec2 get() const {
		return Mouse::get_position();
	}
};

};

#endif