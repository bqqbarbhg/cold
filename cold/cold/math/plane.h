#ifndef _COLD_MATH_PLANE_H
#define _COLD_MATH_PLANE_H

#include <glm/glm.hpp>

namespace cold {

struct BoundingBox;

// 3d plane
struct Plane {
public:
	// Describes the side an object lies in relative to the plane
	enum Side {
		// In front of the plane
		FRONT,
		// Behind the plane
		BACK,
		// Intersecting with the plane
		INTERSECT,
	};
	
	explicit Plane(const glm::vec4& v);

	// Returns which side a bounding box is from the plane
	// box: Box to test the side
	Side get_side(const BoundingBox& box) const;

	// Returns whether the plane intersects `box`
	// box: Box to test intersection against
	bool intersects(const BoundingBox& box) const;

	// Returns dot product with `v`
	// 0.0 if the vector lies within the plane
	// Positive if the vector is in front of the plane
	// Negative if the vector is behind the plane
	// v: Vector to get the dot product with
	float dot(const glm::vec3& v) const;

	// Returns the direction of the plane
	glm::vec3 get_direction() const { return glm::vec3(vector.x, vector.y, vector.z); }

	// Returns the offset from the origin
	float get_offset() const { return vector.w; }

	// Vector representing the plane
	glm::vec4 vector;
};

}

#endif