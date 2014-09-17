#ifndef _COLD_ENGINE_ENTITY_H
#define _COLD_ENGINE_ENTITY_H

#include <cold/engine/handle.h>

namespace cold {

class Scene;
class Entity {
public:
	enum Flags {
		FLAG_NONE		= 0,
		FLAG_UPDATE		= 1 << 0,
		FLAG_DRAW		= 1 << 1,
	};
	virtual Flags get_flags() const { return FLAG_NONE; }
	Entity();
	virtual ~Entity();
	virtual void initialize(Scene *scene);
	virtual void update(float elapsed) { }
	virtual void draw() { }
	handle get_handle() const { return handle; }
protected:
	friend class Scene;
	Scene* scene;
private:
	handle handle;
};

}

#endif