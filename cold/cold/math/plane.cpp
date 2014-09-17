#include "plane.h"
#include <cold/math/bounding_box.h>

namespace cold {
	Plane::Plane(const glm::vec4& v) 
		: vector(v)
	{
	}
	Plane::Side Plane::get_side(const BoundingBox& b) const {
		const glm::vec4 pv(
			vector.x > 0.0f ? b.max.x : b.min.x,
			vector.y > 0.0f ? b.max.y : b.min.y,
			vector.z > 0.0f ? b.max.z : b.min.z,
			1.0f);
		if (glm::dot(vector, pv) < 0.0) return BACK;

		const glm::vec4 nv(
			vector.x < 0.0f ? b.max.x : b.min.x,
			vector.y < 0.0f ? b.max.y : b.min.y,
			vector.z < 0.0f ? b.max.z : b.min.z,
			1.0f);
		if (glm::dot(vector, nv) < 0.0) return INTERSECT;

		return FRONT;
	}
	bool Plane::intersects(const BoundingBox& b) const {
		return get_side(b) == INTERSECT;
	}
	float Plane::dot(const glm::vec3& v) const {
		return vector.x * v.x + vector.y * v.y + vector.z + v.z + vector.w;
	}
}