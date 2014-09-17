#ifndef _COLD_MATH_BOUNDING_FRUSTUM_H
#define _COLD_MATH_BOUNDING_FRUSTUM_H

#include <glm/glm.hpp>
#include <cold/math/plane_iterator.h>

namespace cold {

struct BoundingBox;

// A 3d bounding frustum
struct BoundingFrustum {
public:
	// Retuns a collection of planes defining the frustum
	Planes<BoundingFrustum> get_planes() const;

	// Returns whether the frustum intersects `box`
	// box: A bounding box to test intersection against
	bool intersects(const BoundingBox& box) const;

	// Matrix representing the frustum
	glm::mat4 matrix;
};

template <>
struct PlaneData<BoundingFrustum> {
	const static int count = 6;
	explicit PlaneData(const BoundingFrustum& f) : frustum(f) { }
	Plane get(unsigned int id);
	const BoundingFrustum& frustum;
};

}

#endif