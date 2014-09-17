#include "physical.h"

#include <algorithm>
#include <cold/engine/scene.h>
#include <cold/engine/map.h>
#include <cold/physics/aabb.h>

using namespace glm;
namespace cold {

EntityPhysical::EntityPhysical(glm::vec3 pos, glm::vec3 size)
	: pos(pos), size(size)
{
}

BoundingBox EntityPhysical::get_bounding_box() const {
	return BoundingBox(pos, pos + size);
}
void EntityPhysical::update_physics() {
	on_ground = false;
	int xs = (int)pos.x, ys = (int)pos.y, zs = (int)pos.z;
	int xe = (int)(pos.x + size.x) + 1, ye = (int)(pos.y + size.y) + 1, ze = (int)(pos.z + size.z) + 1;
	BoundingBox bb = get_bounding_box();

	for (int i = xs; i != xe; i++) {
		for (int j = ys; j != ye; j++) {
			for (int k = zs; k != ze; k++) {
				if (!scene->map->get_block(i, j, k)->is_solid())
					continue;
				vec3 diff;

				/*if (aabb::intersection_depth(bb, BoundingBox(vec3(i, j, k), vec3(i + 1, j + 1, k + 1)), diff)) {
					aabb::Direction dir = aabb::intersection_direction(diff);
					pos += diff;
					switch (dir) {
					case X: if (sign(vel.x) != sign(diff.x)) vel.x = 0.0f; break;
					case Z: if (sign(vel.z) != sign(diff.z)) vel.z = 0.0f; break;
					case Y: {
						if (sign(vel.y) != sign(diff.y)) {
							on_ground = true;
							vel.y = 0.0f;
						}
					} break;
					}
					bb = get_bounding_box();
				}*/
			}
		}
	}
}
void EntityPhysical::update(float elapsed) {
	vel *= glm::vec3(1.0f, 1.0f, 1.0f) - (on_ground ? friction_ground : friction_air) * elapsed;
	vel += scene->gravity * elapsed;
	pos += vel * elapsed;
	update_physics();
}
vec3 EntityPhysical::get_center() const {
	return pos + size * 0.5f;
}

}