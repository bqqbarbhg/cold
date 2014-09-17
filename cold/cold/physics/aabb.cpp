#include "aabb.h"
#include <cold/math/bounding_box.h>
#include <cold/math/rectangle.h>

namespace cold {
namespace aabb {

bool intersection_depth(const BoundingBox& a, const BoundingBox& b, glm::vec3& v) {
	glm::vec3 halfA = a.get_size() * 0.5f;
	glm::vec3 halfB = b.get_size() * 0.5f;
	glm::vec3 centerA = a.min + halfA;
	glm::vec3 centerB = b.min + halfB;
	glm::vec3 diff = centerA - centerB;
	glm::vec3 dist = halfA + halfB;
	if (glm::abs(diff.x) >= dist.x || glm::abs(diff.y) >= dist.y || glm::abs(diff.z) >= dist.z)
		return false;

	v = glm::vec3(
		(diff.x > 0 ? dist.x : -dist.x) - diff.x,
		(diff.y > 0 ? dist.y : -dist.y) - diff.y,
		(diff.z > 0 ? dist.z : -dist.z) - diff.z);
	return true;
}

Direction intersection_direction(glm::vec3& v) {
	float ax = glm::abs(v.x);
	float ay = glm::abs(v.y);
	float az = glm::abs(v.z);
	if (ax < ay) {
		if (ax < az) {
			v.y = v.z = 0.0f;
			return X;
		} else {
			v.x = v.y = 0.0f;
			return Z;
		}
	} else if (ay < az) {
		v.x = v.z = 0.0f;
		return Y;
	} else {
		v.x = v.y = 0.0f;
		return Z;
	}
}

bool intersection_depth(const Rectangle& a, const Rectangle& b, glm::vec2& v) {
	glm::vec2 halfA = a.size * 0.5f;
	glm::vec2 halfB = b.size * 0.5f;
	glm::vec2 centerA = a.position + halfA;
	glm::vec2 centerB = b.position + halfB;
	glm::vec2 diff = centerA - centerB;
	glm::vec2 dist = halfA + halfB;
	if (glm::abs(diff.x) >= dist.x || glm::abs(diff.y) >= dist.y)
		return false;

	v = glm::vec2(
		(diff.x > 0 ? dist.x : -dist.x) - diff.x,
		(diff.y > 0 ? dist.y : -dist.y) - diff.y);
	return true;
}

Direction intersection_direction(glm::vec2& v) {
	float ax = glm::abs(v.x);
	float ay = glm::abs(v.y);
	if (ax < ay) {
		v.y = 0.0f;
		return X;
	} else {
		v.x = 0.0f;
		return Y;
	}
}

Intersection<glm::vec3> intersect(const BoundingBox& a, const BoundingBox& b) {
	glm::vec3 v;
	if (!intersection_depth(a, b, v))
		return Intersection<glm::vec3>();
	Direction d = intersection_direction(v);
	return Intersection<glm::vec3>(d, v);
}

Intersection<glm::vec2> intersect(const Rectangle& a, const Rectangle& b) {
	glm::vec2 v;
	if (!intersection_depth(a, b, v))
		return Intersection<glm::vec2>();
	Direction d = intersection_direction(v);
	return Intersection<glm::vec2>(d, v);
}

}
}