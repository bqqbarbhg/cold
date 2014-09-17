#ifndef _COLD_UI_CONTROL_H
#define _COLD_UI_CONTROL_H

#include <cold/math/rectangle.h>
#include <glm/glm.hpp>

namespace cold {
class SpriteBatch;
namespace ui {

class Control {
public:
	Control() : bounds() { }
	Control(const Rectangle& b) : bounds(b) { }
	Control(const Rectangle& b, const glm::vec4& c) : bounds(b), color(c) { }
	virtual ~Control() { }
	virtual void draw(SpriteBatch& sb) const = 0;
	glm::vec4 color;
	Rectangle bounds;
};

} }

#endif