#include "panel.h"
#include <cold/render/util/sprite_batch.h>

namespace cold { namespace ui {

void Panel::draw(SpriteBatch &sb) const {
	sb.draw(bounds.position, color, bounds.size);
	Container::draw(sb);
}

} }