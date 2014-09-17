#include "line_graph.h"
#include <cold/render/util/sprite_batch.h>
#include <cold/render/vertex_declaration.h>
#include <cold/render/types.h>
#include <cold/render/util/line_triangulation.h>
#include <algorithm>
#include <glm/ext.hpp>

namespace cold { namespace ui {

const unsigned int LineGraph::vert_stride = 6;
const unsigned int LineGraph::segm_stride = vert_stride * 4;

LineGraph::LineGraph(const Rectangle& r, const glm::vec4& c, Handle<Font> fnt, unsigned int s, float w)
	: Control(r)
	, index_buffer(DATA_UNSIGNED_SHORT)
	, vertex_data(segm_stride * s)
	, value_data(s)
	, segments(s), width(w), index(0)
	, font(fnt)
	, first(s)
{
	COLD_DEBUG_ASSERT(s > 0);
	float *f = vertex_data.begin();
	float ff = 0.0f;
	float step = 1.0f / s;
	while (f != vertex_data.end()) {
		*f++ = ff;
		*f++ = 0.0f;
		*f++ = c.r; *f++ = c.g; *f++ = c.b; *f++ = c.a;
		*f++ = ff;
		*f++ = w;
		*f++ = c.r; *f++ = c.g; *f++ = c.b; *f++ = c.a;

		ff += step;
	}
	UniqueArray<c_ushort> cu(s * 6);
	c_ushort i = 0;
	c_ushort base = 0;
	c_ushort vals[] = { 0, 1, 2, 1, 3, 2 };
	std::generate(cu.begin(), cu.end(), [&](){ c_ushort u = base + vals[i++]; if (i == 6) { i = 0; base += 4; } return u; });
	
	index_buffer.set_indices(cu.begin(), cu.size());
}

void LineGraph::push(float f) {
	value_data[index++] = f;
	index %= segments;
	if (first > 0)
		first--;
	update_graph();
}
namespace {
struct lg_iterator {
	lg_iterator(float* a, int b, int m, float r, float w, float xs)
		: arr(a), base(b), index(0), mod(m), r(r), w(w), xs(xs)
	{
	}
	lg_iterator(unsigned int e)
		: index(e)
	{
	}
	glm::vec2 operator* () const {
		return glm::vec2(index * xs, (w - arr[(base + index) % mod]) * r + 1.0f);
	}
	void operator++() {
		index++;
	}
	bool operator==(const lg_iterator& m) const {
		return index == m.index;
	}
	bool operator!=(const lg_iterator& m) const {
		return index != m.index;
	}
	float* arr;
	float r, w, xs;
	unsigned int index, base, mod;
};
}
void LineGraph::update_graph() {
	max = min = value_data[0];
	for (unsigned int i = 1; i < segments - first; i++) {
		float f = value_data[i];
		min = f < min ? f : min;
		max = f > max ? f : max;
	}
	float r = 1.0f / (max - min) * 0.9f;
	float w = min;
	if (max == min) {
		r = 1.0f;
		w -= 0.5f;
	}
	float *wptr = vertex_data.begin() + first * segm_stride;
	line_triangulate(
		lg_iterator(value_data.begin(), index - segments + first, value_data.size(), r, w, 1.0f / segments),
		lg_iterator(value_data.size() - first), [&](const glm::vec2* ptr) {
			for (int i = 0; i < 4; i++) {
				wptr[0] = ptr[i].x;
				wptr[1] = ptr[i].y;
				wptr += vert_stride;
			}
		}
		, width);

	int mlen;
	mlen = sprintf(minbuf, "%.3f", min);
	minlen = font->measure(minbuf, minbuf + mlen).x;
	mlen = sprintf(maxbuf, "%.3f", max);
	maxlen = font->measure(maxbuf, maxbuf + mlen).x;
}

void LineGraph::draw(SpriteBatch& sb) const {
	sb.render_batch();

	SpriteBatch::vert_decl_no_tex.apply(vertex_data.begin());
	index_buffer.apply();
	if (first < segments) {
		sb.apply_shader(nullptr, sb.get_transform() * glm::translate(bounds.position.x, bounds.position.y, 0.0f) * glm::scale(bounds.size.x, bounds.size.y, 0.0f));
		index_buffer.draw(DRAW_TRIANGLES, (segments - first) * 6, first * 6);
	}
	sb.draw_string(font, maxbuf, bounds.position + glm::vec2(bounds.size.x - maxlen, 0.0f));
	sb.draw_string(font, minbuf, bounds.position + glm::vec2(bounds.size.x - minlen, bounds.size.y - font->impl->get_height()));
}

} }