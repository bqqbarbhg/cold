#ifndef _COLD_MATH_BOUNDING_BOX_H
#define _COLD_MATH_BOUNDING_BOX_H

#include <glm/glm.hpp>

namespace cold {

// 3D bounding box (AABB) stored as (min, max)
struct BoundingBox {
public:
	// Creates a new (invalid) bounding box
	// Should be scaled either manually setting `min` and `max` or
	// calling the overloaded `expand` function before use
	BoundingBox() : min(FLT_MAX, FLT_MAX, FLT_MAX), max(-FLT_MAX, -FLT_MAX, -FLT_MAX) { }

	// Creates a new (zero-sized) bounding box at point
	explicit BoundingBox(const glm::vec3& point);

	// Creates a new bounding box between `min` and `max`
	BoundingBox(const glm::vec3& min, const glm::vec3& max);

	// Returns whether the bounding box intersects `other`
	// other: The bounding box to test intersection against
	bool intersects(const BoundingBox& other) const;

	// Returns whether `point` is inside the bounding box
	bool contains(const glm::vec3& point) const;

	// Expands the bounding box so that it contains `point`
	void expand(const glm::vec3& point);

	// Expands the bounding box so that it contains `box`
	void expand(const BoundingBox& box);

	// Moves the bounding box by `amount`
	void move(const glm::vec3& amount) {
		min += amount, max += amount;
	}

	// Returns the center of the bounding box
	glm::vec3 get_center() const {
		return (min + max) * 0.5f;
	}

	// Returns the size of the bounding box
	glm::vec3 get_size() const {
		return max - min;
	}

	// Minimum vertex of the bounding box
	glm::vec3 min;

	// Maximum vertex of the bounding box
	glm::vec3 max;
};

}

#endif