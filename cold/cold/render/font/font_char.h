#ifndef _COLD_RENDER_FONT_FONT_CHAR_H
#define _COLD_RENDER_FONT_FONT_CHAR_H

#include <cold/resource/handle.h>
#include <cold/render/texture.h>
#include <cold/math/rectangle.h>
#include <glm/glm.hpp>

namespace cold { namespace impl {

class FontChar {
public:
	bool visible;
	glm::vec2 offset;
	Rectangle bounds;
	Handle<Texture> texture;
};

} }

#endif