#include "rectangle.h"

namespace cold {

Rectangle Rectangle::Unit = Rectangle(0.0f, 0.0f, 1.0f, 1.0f);

Rectangle::Rectangle()
{
}
Rectangle::Rectangle(const glm::vec2& p, const glm::vec2& s)
	: position(p), size(s)
{
}
Rectangle::Rectangle(float x, float y, float w, float h)
	: position(x, y), size(w, h)
{
}

}