#ifndef _COLD_PHYSICS_AABB_H
#define _COLD_PHYSICS_AABB_H

#include <glm/glm.hpp>

namespace cold {
struct BoundingBox;
struct Rectangle;

// Advanced AABB intersection
// Returns information on how to resolve collisions
namespace aabb {


// Intersection direction (if any)
enum Direction {
	// No intersection
	NONE,
	// Intersects from the X axis
	X,
	// Intersects from the Y axis
	Y,
	// Intersects from the Z axis
	Z,
};

// An intersection between two bounding boxes
// <T>: Intersection depth (vec2 or vec3 depending on the dimension)
template <typename T>
struct Intersection {
public:
	Intersection() : direction(NONE) { }
	Intersection(Direction d, const T& t) : direction(d), depth(t) { }

	// Direction or NONE of the intersection
	Direction direction;

	// Depth of the intersection
	// Only the axis of `direction` is valid (none are valid if it's NONE)
	T depth;

	operator bool() const {
		return direction != NONE;
	}
};

// Intersects two 3D AABBs
// The returned vector added to `a` will resolve the collision
// a: The first bounding box (add return value to fix)
// b: The second bounding box (subtract return value to fix)
Intersection<glm::vec3> intersect(const BoundingBox& a, const BoundingBox& b);

// Intersects two 2D AABBs
// The returned vector added to `a` will resolve the collision
// a: The first bounding rectangle (add return value to fix)
// b: The second bounding rectangle (subtract return value to fix)
Intersection<glm::vec2> intersect(const Rectangle& a, const Rectangle& b);

}

}

#endif