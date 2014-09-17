#include "entity.h"

namespace cold {

Entity::Entity()
{
}
Entity::~Entity()
{
}
void Entity::initialize(Scene *s) {
	scene = s;
}

}