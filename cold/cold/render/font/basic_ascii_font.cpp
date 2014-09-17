#include "basic_ascii_font.h"

#include <cold/render/font/font_char.h>
#include <string>

namespace cold { namespace impl {

const glm::vec2 BasicASCIIFont::char_size = glm::vec2(1.0f / (float)0x10, 1.0f / (float)0x10);

BasicASCIIFont::BasicASCIIFont(const Handle<Texture>& h)
	: texture(h)
{
}

void BasicASCIIFont::set_char(char_t current) {
	c = current;
}
float BasicASCIIFont::move_next(char_t next) {
	c = next;
	return char_size.x * texture->get_width();
}
void BasicASCIIFont::get_char_info(FontChar& f) {
	f.texture = texture;
	f.bounds.position = glm::vec2(c & 0xf, c >> 4) * char_size;
	f.bounds.size = char_size;
	f.offset = glm::vec2(0.0f);
	f.visible = true;
}
float BasicASCIIFont::get_height() {
	return char_size.y * texture->get_height();
}

} }