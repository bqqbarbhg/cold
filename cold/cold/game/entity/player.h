#ifndef _COLD_GAME_ENTITY_PLAYER_H
#define _COLD_GAME_ENTITY_PLAYER_H

#include <cold/game/entity/physical.h>
#include <glm/glm.hpp>
#include <cold/input/bind.h>

namespace cold {

class EntityPlayer : public EntityPhysical
{
public:
	EntityPlayer(glm::vec3 pos);
	Flags get_flags() const { return (Flags)(EntityPhysical::get_flags() | FLAG_UPDATE | FLAG_DRAW); }
	void update(float elapsed);
	void draw();
private:
	float yaw, pitch;
	Bind<glm::vec2> move_bind;
	Bind<glm::vec2> aim_bind;
	Bind<bool> jump_bind;
};

};

#endif