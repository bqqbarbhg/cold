#include "bounding_box.h"

namespace cold {

BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max)
	: min(min), max(max)
{
}

BoundingBox::BoundingBox(const glm::vec3& point)
	: min(point), max(point)
{
}


bool BoundingBox::intersects(const BoundingBox& other) const {
	return	!( other.max.x < min.x || other.max.y < min.y || other.max.z < max.z
			|| other.min.x > max.x || other.min.y > max.y || other.min.z > max.z);
}

bool BoundingBox::contains(const glm::vec3& v) const {
	return	!( v.x < min.x || v.y < min.y || v.z < min.z
			|| v.x > max.x || v.y > max.y || v.z > max.z);
}

void BoundingBox::expand(const glm::vec3& point) {
	if (min.x > point.x) min.x = point.x;
	if (min.y > point.y) min.y = point.y;
	if (min.z > point.z) min.z = point.z;
	if (max.x < point.x) max.x = point.x;
	if (max.y < point.y) max.y = point.y;
	if (max.z < point.z) max.z = point.z;
}

void BoundingBox::expand(const BoundingBox& box) {
	if (min.x > box.min.x) min.x = box.min.x;
	if (min.y > box.min.y) min.y = box.min.y;
	if (min.z > box.min.z) min.z = box.min.z;
	if (max.x < box.max.x) max.x = box.max.x;
	if (max.y < box.max.y) max.y = box.max.y;
	if (max.z < box.max.z) max.z = box.max.z;
}

};