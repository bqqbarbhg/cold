#ifndef _COLD_UI_PANEL_H
#define _COLD_UI_PANEL_H

#include <cold/ui/container.h>
#include <glm/glm.hpp>

namespace cold { namespace ui {

class Panel : public Container {
public:
	Panel() { }
	Panel(const Rectangle& b, const glm::vec4& c) : Container(b, c) { }
	virtual void draw(SpriteBatch& sb) const;
};

} }

#endif