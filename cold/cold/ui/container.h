#ifndef _COLD_UI_CONTAINER_H
#define _COLD_UI_CONTAINER_H

#include <cold/ui/control.h>
#include <cold/util/unique_ptr.h>
#include <vector>

namespace cold { namespace ui {

class Container : public Control {
public:
	Container() { }
	Container(const Rectangle& b) : Control(b) { }
	Container(const Rectangle& b, const glm::vec4& c) : Control(b, c) { }
	virtual ~Container() { }
	virtual void add(Control* c);
	virtual void draw(SpriteBatch& sb) const;
protected:
	std::vector<UniquePtr<Control>> controls;
};

} }

#endif