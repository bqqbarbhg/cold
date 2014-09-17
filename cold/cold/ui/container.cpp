#include "container.h"

namespace cold { namespace ui {

void Container::draw(SpriteBatch& sb) const {
	for (std::vector<UniquePtr<Control>>::const_iterator it = controls.cbegin(); it != controls.cend(); ++it) {
		(*it)->draw(sb);
	}
}

void Container::add(Control* c) {
	controls.push_back(c);
}

} }