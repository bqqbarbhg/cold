#ifndef _COLD_RENDER_UTIL_LINE_TRIANGULATION_H
#define _COLD_RENDER_UTIL_LINE_TRIANGULATION_H

#include <glm/glm.hpp>
#include <cold/math/geometry.h>

namespace cold {

// TODO(bqq): Non-jagged mode?

// Triangulates a line curve
// <> Iter: Forward iterator of glm::vec2
// <> Func: Output function void(glm::vec2 data[4])
// begin: Begin of the line data
// end: End of the line data
// output: Output function
// width: Line width
template <typename Iter, typename Func>
void line_triangulate(Iter begin, const Iter& end, Func output, float width=1.0f) {
	using namespace glm;
	glm::vec2 points[3];
	glm::vec2 dir, dir_next, normal, norm_next;
	glm::vec2 out[4];
	float iden;
	if (begin == end) return;
	points[0] = *begin; ++begin;
	if (begin == end) return;
	points[1] = *begin; ++begin;

	// First
	dir = normalize(points[1] - points[0]);
	normal = vec2(dir.y, -dir.x);
	out[0] = points[0] + normal * width;
	out[1] = points[0] - normal * width;

	// Middle
	while (begin != end) {
		points[2] = *begin; ++begin;
		dir_next = normalize(points[2] - points[1]);
		norm_next = vec2(dir_next.y, -dir_next.x);
		vec2 d = norm_next * width;
		iden = intersect::cross2(dir, dir_next);
		if (iden == 0.0f) {
			out[2] = points[1] + normal * width;
			out[3] = points[1] - normal * width;
			output(out);
			if (dot(dir, dir_next) < 0.0f) {
				out[0] = out[3];
				out[1] = out[2];
			} else {
				out[0] = out[2];
				out[1] = out[3];
			}
		} else {
			iden = 1.0f / iden;
			bool dt;
			if (dt = dot(dir, dir_next) < 0.0f)
				d = -d;
			out[2] = out[0] + dir * iden * intersect::cross2(points[2] + d - out[0], dir_next);
			out[3] = out[1] + dir * iden * intersect::cross2(points[2] - d - out[1], dir_next);
			output(out);
			if (dt) {
				int oi;
				if (iden < 0.0f) {
					out[1] = out[2];
					oi = 0;
				} else {
					out[0] = out[3];
					oi = 1;
					d = -d;
				}
				float f = iden * intersect::cross2(points[2] - d - out[oi], dir_next);
				if (f < 0.0f || iden * intersect::cross2(points[2] - d - out[oi], dir) > 0.0f)
					out[oi] = out[3 - oi];
				else
					out[oi] += dir * f;
			} else {
				out[0] = out[2];
				out[1] = out[3];
			}
		}

		points[0] = points[1];
		points[1] = points[2];
		dir = dir_next;
		normal = norm_next;
	}

	// Last
	out[2] = points[1] + normal * width;
	out[3] = points[1] - normal * width;
	output(out);
}

}

#endif