#ifndef _COLD_MATH_GEOMETRY_H
#define _COLD_MATH_GEOMETRY_H

#include <glm/glm.hpp>
#include <cold/util/either.h>

namespace cold { namespace intersect {

// Infinite intersection
enum InfiniteIntersection {
	// Every point is shared between the two objects
	ALWAYS,
	// The objects have no points in common
	NEVER,
};

// 2D 'cross' function
inline float cross2(const glm::vec2& a, const glm::vec2& b) {
	return a.x * b.y - a.y * b.x;
}

// (first) float: if intersectin point => a_pos + a_dir * return
// (second) InfiniteIntersection: if parallel => ALWAYS / NEVER
Either<float, InfiniteIntersection> line(const glm::vec2& a_pos, const glm::vec2& a_dir, const glm::vec2& b_pos, const glm::vec2& b_dir);

} }

#endif