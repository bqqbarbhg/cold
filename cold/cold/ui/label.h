#ifndef _COLD_UI_LABEL_H
#define _COLD_UI_LABEL_H

#include <cold/ui/control.h>
#include <cold/render/util/sprite_batch.h>
#include <cold/resource/handle.h>
#include <cold/render/font.h>

namespace cold { namespace ui {

template <typename T>
class Label : public Control {
public:
	Label(const Handle<Font>& f) : font(f) { }
	Label(Handle<Font>&& f) : font(std::move(f)) { }
	virtual void draw(SpriteBatch &sb) const {
		sb.draw_string(font, text, bounds.position);
	}
	Handle<Font> font;
	T text;
};

} }

#endif