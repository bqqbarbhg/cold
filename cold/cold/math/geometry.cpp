#include "geometry.h"

#include <limits>

namespace cold { namespace intersect {

Either<float, InfiniteIntersection> line(const glm::vec2& a_pos, const glm::vec2& a_dir, const glm::vec2& b_pos, const glm::vec2& b_dir) {
	using namespace glm;
	float den = cross2(a_dir, b_dir);
	float num = cross2(a_dir, a_pos - b_pos);
	if (abs(den) <= std::numeric_limits<float>::epsilon()) {
		if (abs(num) <= std::numeric_limits<float>::epsilon())
			return ALWAYS;
		return NEVER;
	}
	return num / den;
}

} }