#ifndef _COLD_RENDER_FONT_FONT_IMPL_H
#define _COLD_RENDER_FONT_FONT_IMPL_H

#include <cold/resource/handle.h>
#include <cold/render/texture.h>
#include <cold/math/rectangle.h>
#include <cold/util/string.h>
#include <utility>

// TODO(bqq): Concurrent-friendly fonts

namespace cold {
namespace impl {
class FontChar;
class FontImpl {
public:
	typedef std::uint32_t char_t;
	virtual void set_char(char_t current) = 0;
	virtual float move_next(char_t next) = 0;
	virtual void get_char_info(FontChar& f) = 0;
	virtual float get_height() = 0;
};

} }

#endif