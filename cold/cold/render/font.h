#ifndef _COLD_RENDER_FONT_H
#define _COLD_RENDER_FONT_H

#include <cold/util/unique_ptr.h>
#include <cold/render/font/font_impl.h>

namespace cold {

// Class that holds a font instance
// Non-copyable
class Font {
public:
	Font(UniquePtr<impl::FontImpl>&& u);
	Font(Font&& f);
	Font& operator=(Font&& f);
	UniquePtr<impl::FontImpl> impl;
	// TODO(bqq): Completely broken, redo font impl
	template <typename T>
	glm::vec2 measure(T begin, const T& end) const {
		if (begin == end) return glm::vec2(0.0f, impl->get_height());
		impl->set_char(*begin);
		float v = 0.0f;
		while (++begin != end) {
			v += impl->move_next(*begin);
		}
		v += impl->move_next(0);
		return glm::vec2(v, 0.0f);
	}
private:
	Font(Font& f);
	Font& operator=(const Font& f);
};

}

#endif