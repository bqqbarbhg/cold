#include "scene.h"

#include <cold/util/assert.h>
#include <cold/engine/map.h>
#include <cold/engine/entity.h>

namespace cold {

Scene::Scene(Map* map)
	: map(map)
{
}
Scene::~Scene() {
	for (std::map<handle, Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		delete it->second;
	}
	delete map;
}

void Scene::add(Entity* e) {
	entities[e->handle = handle_counter++] = e;
	Entity::Flags f = e->get_flags();
	if (f & Entity::FLAG_UPDATE)
		updatable.insert(e);
	if (f & Entity::FLAG_DRAW)
		drawable.insert(e);
	e->initialize(this);
}

void Scene::remove(Entity* e) {
	std::map<handle, Entity*>::iterator it = entities.find(e->handle);
	COLD_ASSERT(it != entities.end());
	entities.erase(it);
	Entity::Flags f = e->get_flags();
	if (f & Entity::FLAG_UPDATE)
		updatable.erase(e);
	if (f & Entity::FLAG_DRAW)
		updatable.erase(e);
	delete e;
}

void Scene::update(float elapsed) {
	for (std::set<Entity*>::iterator it = updatable.begin(); it != updatable.end(); ++it) {
		(*it)->update(elapsed);
	}
}
void Scene::draw() {
	for (std::set<Entity*>::iterator it = drawable.begin(); it != drawable.end(); ++it) {
		(*it)->draw();
	}
}

}