#ifndef _COLD_ENGINE_SCENE_H
#define _COLD_ENGINE_SCENE_H

#include <glm/glm.hpp>
#include <cold/engine/handle.h>
#include <cold/engine/camera.h>
#include <vector>
#include <set>
#include <map>

namespace cold {

class Map;
class Entity;
class EntityUpdatable;
class EntityDrawable;
class Scene {
public:
	Scene(Map *map);
	~Scene();
	void add(Entity* e);
	void remove(Entity* e);

	void update(float elapsed);
	void draw();

	Entity* get_entity(handle h);
	const Entity* get_entity(handle h) const;

	Camera camera;
	Map *map;
	glm::vec3 gravity;
private:
	handle handle_counter;
	std::set<Entity*> updatable;
	std::set<Entity*> drawable;
	std::map<handle, Entity*> entities;
};

}

#endif