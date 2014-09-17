#include "bounding_frustum.h"
#include <cold/math/bounding_box.h>

namespace cold {

bool BoundingFrustum::intersects(const BoundingBox& b) const {
	for (Plane& plane : get_planes()) {
		if (plane.get_side(b) == Plane::BACK)
			return false;
	}
	return true;
}

Planes<BoundingFrustum> BoundingFrustum::get_planes() const {
	return Planes<BoundingFrustum>(PlaneData<BoundingFrustum>(*this));
}

Plane PlaneData<BoundingFrustum>::get(unsigned int id) {
	switch (id) {
		case 0: return Plane(frustum.matrix[3] + frustum.matrix[0]);
		case 1: return Plane(frustum.matrix[3] - frustum.matrix[0]);
		case 2: return Plane(frustum.matrix[3] + frustum.matrix[1]);
		case 3: return Plane(frustum.matrix[3] - frustum.matrix[1]);
		case 4: return Plane(frustum.matrix[3] + frustum.matrix[2]);
		case 5: return Plane(frustum.matrix[3] - frustum.matrix[2]);
	}
	throw "Plane index out of range";
}

}