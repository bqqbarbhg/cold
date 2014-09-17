#ifndef _COLD_RENDER_FONT_BASIC_ASCII_FONT_H
#define _COLD_RENDER_FONT_BASIC_ASCII_FONT_H

#include <cold/render/font/font_impl.h>

namespace cold { namespace impl {
class BasicASCIIFont : public FontImpl {
public:
	BasicASCIIFont (const Handle<Texture>& tex);
	virtual void set_char(char_t current);
	virtual float move_next(char_t next);
	virtual void get_char_info(FontChar& f);
	virtual float get_height();
private:
	const static glm::vec2 char_size;
	char_t c;
	Handle<Texture> texture;
};

} }

#endif