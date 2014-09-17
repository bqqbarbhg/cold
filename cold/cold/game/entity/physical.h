#ifndef _COLD_GAME_ENTITY_PHYSICAL_H
#define _COLD_GAME_ENTITY_PHYSICAL_H

#include <glm/glm.hpp>
#include <cold/engine/entity.h>
#include <cold/math/bounding_box.h>

namespace cold {

class EntityPhysical : public Entity {
public:
	EntityPhysical(glm::vec3 pos, glm::vec3 size);
	virtual Flags get_flags() const { return (Flags)(Entity::get_flags() | FLAG_UPDATE); }
	virtual void update(float elapsed);
	glm::vec3 get_center() const;
	BoundingBox get_bounding_box() const;
protected:
	glm::vec3 pos, vel;
	glm::vec3 size;
	bool on_ground;
	glm::vec3 friction_ground, friction_air;
private:
	void update_physics();
};

}

#endif