#ifndef _COLD_RENDER_FONT_FNT_FONT_H
#define _COLD_RENDER_FONT_FNT_FONT_H

#include <cold/resource/handle.h>
#include <cold/render/texture.h>
#include <cold/render/font/font_impl.h>
#include <unordered_map>
#include <vector>
#include <istream>

namespace cold { namespace impl {

class FntFont : public FontImpl {
public:
	struct CharInfo {
		Rectangle bounds;
		glm::vec2 offset;
		float advance;
		unsigned int page, channel;
		bool exists, visible;
	};
	struct CharRange {
		CharRange(char_t c) : first(c) { }
		void push(char_t p, const CharInfo& c) { last = p; chars.push_back(c); }
		char_t first, last;
		std::vector<CharInfo> chars;
	};
	virtual void set_char(char_t current);
	virtual float move_next(char_t next);
	virtual void get_char_info(FontChar& f);
	virtual float get_height() { return height; }
	bool load_text_fnt(const std::string& name);
private:
	float height;
	CharInfo* ch;
	std::vector<CharRange> ranges;
	CharInfo default_char;
	std::vector<Handle<Texture>> pages;
};

} }

#endif