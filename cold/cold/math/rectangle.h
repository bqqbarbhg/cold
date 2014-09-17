#ifndef _COLD_MATH_RECTANGLE_H
#define _COLD_MATH_RECTANGLE_H

#include <glm/glm.hpp>

namespace cold {

// 2D rectangle stored as (position, size)
struct Rectangle {
public:
	Rectangle();
	Rectangle(const glm::vec2& p, const glm::vec2& s);
	Rectangle(float x, float y, float w, float h);

	// Returns the x-coordinate of the left edge
	float get_left() const { return position.x; }

	// Returns the x-coordinate of the right edge
	float get_right() const { return position.x + size.x; }

	// Returns the y-coordinate of the top edge
	float get_top() const { return position.y; }

	// Returns the y-coordinate of the bottom edge
	float get_bottom() const { return position.y + size.y; }

	// The minimum vertex of the rectangle
	glm::vec2 position;

	// The size of the rectangle (width, height)
	glm::vec2 size;

	// Rectangle with position zero and size of 1.0
	static Rectangle Unit;
};

}

#endif