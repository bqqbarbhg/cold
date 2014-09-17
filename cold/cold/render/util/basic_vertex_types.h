#ifndef _COLD_RENDER_UTIL_BASIC_VERTEX_TYPES_H
#define _COLD_RENDER_UTIL_BASIC_VERTEX_TYPES_H

#include <cold/render/types.h>
#include <glm/glm.hpp>

namespace cold {

struct VTPosition {
	VTPosition(c_float x, c_float y, c_float z)
		: x(x), y(y), z(z)
	{ }
	VTPosition(const glm::vec3& p)
		: x(p.x), y(p.y), z(p.z)
	{ }
	c_float x, y, z;
};
struct VTPositionColor {
	VTPositionColor(c_float x, c_float y, c_float z, c_float r, c_float g, c_float b)
		: x(x), y(y), z(z), r(r), g(g), b(b)
	{ }
	VTPositionColor(const glm::vec3& p, const glm::vec3& c)
		: x(p.x), y(p.y), z(p.z), r(c.x), g(c.y), b(c.z)
	{ }
	c_float x, y, z;
	c_float r, g, b;
};
struct VTPositionTexture {
	VTPositionTexture(c_float x, c_float y, c_float z, c_float u, c_float v)
		: x(x), y(y), z(z), u(u), v(v)
	{ }
	VTPositionTexture(const glm::vec3& p, const glm::vec2& t)
		: x(p.x), y(p.y), z(p.z), u(t.x), v(t.y)
	{ }
	c_float x, y, z;
	c_float u, v;
};
struct VTPositionColorTexture {
	VTPositionColorTexture(c_float x, c_float y, c_float z, c_float r, c_float g, c_float b, c_float u, c_float v)
		: x(x), y(y), z(z), r(r), g(g), b(b), u(u), v(v)
	{ }
	VTPositionColorTexture(const glm::vec3& p, const glm::vec3& c, const glm::vec2& t)
		: x(p.x), y(p.y), z(p.z), r(c.x), g(c.y), b(c.z), u(t.x), v(t.y)
	{ }
	c_float x, y, z;
	c_float r, g, b;
	c_float u, v;
};

}

#endif