#include "fnt_font.h"

#include <cold/util/buffered_stream.h>
#include <cold/util/config_scanner.h>
#include <cold/resource/resource_loader.h>
#include <cold/resource/resource_manager.h>
#include <cold/util/unique_ptr.h>
#include <cold/render/font/font_char.h>
#include <sstream>
#include <map>

namespace cold { namespace impl {

void FntFont::set_char(char_t c) {
	if (!c) return;
	for (auto it = ranges.begin(); it != ranges.end(); ++it) {
		if (c < it->first) break;
		if (c > it->last) continue;
		ch = &it->chars[c - it->first];
		if (!ch->exists) ch = &default_char;
		return;
	}
	ch = &default_char;
}

float FntFont::move_next(char_t c) {
	float f = ch->advance;
	set_char(c);
	return f;
}

void FntFont::get_char_info(FontChar& f) {
	f.texture = pages[ch->page];
	f.bounds = ch->bounds;
	f.offset = ch->offset;
}

bool FntFont::load_text_fnt(const std::string& name) {
	using namespace ConfigScanner;
	UniquePtr<std::istream> i = ResourceLoader::get()->load_stream(name + ".fnt");
	BufferedStream b(*i, 64);
	Token token;
	char_t char_id = 0;
	std::map<char_t, CharInfo> cinfos;

	// Parse and fill cinfos
	while (true)
	{
		if (!scan(b, token, false)) return false;
		if (token.type == Token::IDENTIFIER) {
			bool common = false;
			if (token.text == "common") common = true;
			else if (token.text != "char") {
				do {
					if (!scan(b, token, false))
						return false;
					if (token.type == Token::END_OF_FILE)
						break;
				} while (token.type != Token::NEWLINE);
				continue;
			}
			if (!scan(b, token, false)) return false;
			while (token.type != Token::NEWLINE) {
				if (token.type != Token::IDENTIFIER) return false;
				std::string k(token.text);
				if (scan(b, token, false) && token.type == Token::ASSIGN
				 && scan(b, token, false) && token.type == Token::NUMBER) {
					long v = token.number;
					if (common) {
						if (k == "lineHeight") height = (float)v;
						else if (k == "pages") pages.resize(v);
					} else {
						if (k == "id") cinfos[char_id = (char_t)v].exists = true;
						else if (k == "x") cinfos[char_id].bounds.position.x = (float)v;
						else if (k == "y") cinfos[char_id].bounds.position.y = (float)v;
						else if (k == "width") cinfos[char_id].bounds.size.x = (float)v;
						else if (k == "height") cinfos[char_id].bounds.size.y = (float)v;
						else if (k == "xoffset") cinfos[char_id].offset.x = (float)v;
						else if (k == "yoffset") cinfos[char_id].offset.y = (float)v;
						else if (k == "xadvance") cinfos[char_id].advance = (float)v;
						else if (k == "page") cinfos[char_id].page = (unsigned int)v;
						else if (k == "chnl") cinfos[char_id].channel = (unsigned int)v;
					}
				} else
					return false;
				if (!scan(b, token, false)) return false;
			}
		} else if (token.type == Token::END_OF_FILE) {
			break;
		} else do {
			if (!scan(b, token, false)) return false;
			if (token.type == Token::END_OF_FILE)
				break;
		} while (token.type != Token::NEWLINE);
	}
	// Load texture pages
	for (unsigned int i = 0; i < pages.size(); i++) {
		std::ostringstream s;
		s << name << "_" << i;
		pages[i] = ResourceManager<Texture>::get(s.str());
	}
	// Set default character
	char_t def_priority[] = { (char_t)0xFFFF, (char_t)' ' };
	default_char.exists = false;
	for (char_t *cc = def_priority, *ce = def_priority + sizeof(def_priority) / sizeof(*def_priority); cc != ce; cc++) {
		auto it = cinfos.find(*cc);
		if (it != cinfos.end()) {
			default_char = it->second;
			glm::vec2 ps = 1.0f / pages[default_char.page]->get_size();
			default_char.bounds.position *= ps;
			default_char.bounds.size *= ps;
			break;
		}
	}
	if (!default_char.exists) {
		default_char.visible = false;
		default_char.advance = 15.0f;
		default_char.exists = true;
	}
	// Create character ranges
	char_t last = -1;
	CharInfo nop;
	nop.exists = false;
	for (auto it = cinfos.cbegin(); it != cinfos.cend(); ++it) {
		if (last == (char_t)-1 || it->first != last + 1) {
			if (last != (char_t)-1 && it->first < last + 10) {
				do {
					ranges.back().push(++last, nop);
				} while (last != it->first - 1);
			}
			else
				ranges.push_back(CharRange(it->first));
		}
		glm::vec2 ps = 1.0f / pages[it->second.page]->get_size();
		ranges.back().push(it->first, it->second);
		ranges.back().chars.back().bounds.position *= ps;
		ranges.back().chars.back().bounds.size *= ps;
		ranges.back().chars.back().visible = true;
		last = it->first;
	}
	return true;
}

} }