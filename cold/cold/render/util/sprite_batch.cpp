#include "sprite_batch.h"

#include <cold/render/types.h>
#include <cold/render/texture.h>
#include <cold/render/shader.h>
#include <cold/render/vertex_declaration.h>
#include <cold/render/vertex_element.h>
#include <cold/render/enums.h>
#include <cold/util/assert.h>
#include <cold/math/rectangle.h>
#include <cold/render/font.h>
#include <cold/render/impl/debug.h>
#include <cold/render/font/font_char.h>

#include <glm/ext.hpp>

#include <limits>

namespace cold {

Shader SpriteBatch::shader = Shader::Uninitialized, SpriteBatch::shader_no_tex = Shader::Uninitialized;
bool SpriteBatch::initialized = false;
const char *SpriteBatch::vert_shader =
"	uniform mat4 w;					                    \n"
"	varying vec2 v;                                     \n"
"	varying vec4 c;                                     \n"
"	void main() {					                    \n"
"	    gl_Position = w * vec4(gl_Vertex.xy, 0.5, 1.0); \n"
"		c = gl_Color;                                   \n"
"	    v = gl_MultiTexCoord0.st;                       \n"
"	}								                    \n"
;
const char *SpriteBatch::frag_shader =
"	uniform sampler2D t;                                \n"
"	varying vec2 v;                                     \n"
"	varying vec4 c;                                     \n"
"	void main() {                                       \n"
"	    gl_FragColor = texture2D(t, v) * c;             \n"
"	}                                                   \n"
;
const char *SpriteBatch::vert_shader_no_tex =
"	uniform mat4 w;                                     \n"
"	varying vec4 c;                                     \n"
"	void main() {                                       \n"
"		gl_Position = w * vec4(gl_Vertex.xy, 0.5, 1.0); \n"
"		c = gl_Color;                                   \n"
"	}                                                   \n"
;
const char *SpriteBatch::frag_shader_no_tex =
"	varying vec4 c;                                     \n"
"	void main() {                                       \n"
"	    gl_FragColor = c;                               \n"
"	}                                                   \n"
;
const VertexElement SpriteBatch::vert_elems[] = {
	{ VertexElement::POSITION, DATA_FLOAT, 2, 2 * sizeof(c_float) },
	{ VertexElement::TEXTURE_COORDINATE, DATA_FLOAT, 2, 2 * sizeof(c_float) },
	{ VertexElement::COLOR, DATA_FLOAT, 4, 4 * sizeof(c_float) },
	{ VertexElement::END },
};
const VertexDeclaration SpriteBatch::vert_decl = VertexDeclaration(vert_elems);

const VertexElement SpriteBatch::vert_elems_no_tex[] = {
	{ VertexElement::POSITION, DATA_FLOAT, 2, 2 * sizeof(c_float) },
	{ VertexElement::COLOR, DATA_FLOAT, 4, 4 * sizeof(c_float) },
	{ VertexElement::END },
};
const VertexDeclaration SpriteBatch::vert_decl_no_tex = VertexDeclaration(vert_elems_no_tex);

void SpriteBatch::initialize() { COLD_RENDER_DEBUG
	if (initialized) return;
	initialized = true;
	shader = Shader();
	shader.compile(vert_shader, frag_shader);
	shader_no_tex = Shader();
	shader_no_tex.compile(vert_shader_no_tex, frag_shader_no_tex);
}

namespace {

template <typename T>
void init_index_buffer(IndexBuffer& i, unsigned int count) {
	UniqueArray<T> arr(count * 6);
	unsigned int n = 0;
	for (T* p = arr.begin(); p != arr.end(); n += 4) {
		*p++ = n;
		*p++ = n + 1;
		*p++ = n + 2;

		*p++ = n + 1;
		*p++ = n + 2;
		*p++ = n + 3;
	}
	i.set_indices(arr.begin(), arr.size());
}

}

SpriteBatch::SpriteBatch(unsigned int max_batch)
	: index_buffer(IndexBuffer::Uninitialized)
	, vertex_data(max_batch * 4 * (2 + 2 + 4))
	, current_tex(nullptr)
	, begun(false)
{
	SpriteBatch::initialize();
	max_batch *= 2;
	if (max_batch * 4 > std::numeric_limits<c_ushort>::max()) {
		index_buffer = IndexBuffer(DATA_UNSIGNED_SHORT);
		init_index_buffer<c_ushort>(index_buffer, max_batch);
	} else {
		index_buffer = IndexBuffer(DATA_UNSIGNED_INT);
		init_index_buffer<c_uint>(index_buffer, max_batch);
	}
}

SpriteBatch::~SpriteBatch() {
	COLD_ASSERT(!begun);
}

void SpriteBatch::set_bounds(const Rectangle& r) {
	transform
		= glm::ortho(r.get_left(), r.get_right(), r.get_bottom(), r.get_top(), -1.0f, 1.0f)
		* glm::translate(-0.5f / r.size.x, -0.5f / r.size.y, 0.0f);
}

void SpriteBatch::begin(const BlendState& b) {
	COLD_ASSERT(!begun);
	begun = true;
	ptr = vertex_data.begin();
	blend_state = b;
	num_sprites = 0;
}

namespace {
	void rotate_vertices(int data_size, float* p, float* ptr, float rotation, const glm::vec2& position) {
		float a, b;
		float tsin = glm::sin(rotation);
		float tcos = glm::cos(rotation);
		for (; p<ptr; p += data_size) {
			a = p[0] - position.x;
			b = p[1] - position.y;
			p[0] = tcos * a - tsin * b + position.x;
			p[1] = tsin * a + tcos * b + position.y;
		}
	}
}

void SpriteBatch::draw(const Texture& texture, const glm::vec2& position, const glm::vec4& color, const glm::vec2& size, float rotation, const glm::vec2& origin, const Rectangle& clip) {
	if (current_tex) {
		if (texture != *current_tex) {
			render_batch();
			current_tex = &texture;
		}
	} else {
		render_batch();
		current_tex = &texture;
	}

	if (ptr == vertex_data.end())
		render_batch();

	glm::vec2 s = texture.get_size();
	glm::vec2 q = s * clip.size * origin * size;
	float x = position.x - q.x;
	float y = position.y - q.y;
	float w = texture.get_width() * clip.size.x * size.x;
	float h = texture.get_height() * clip.size.y * size.y;

	float *p = ptr;
	*ptr++ = x; *ptr++ = y;
	*ptr++ = clip.get_left(); *ptr++ = clip.get_top();
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	*ptr++ = x + w; *ptr++ = y;
	*ptr++ = clip.get_right(); *ptr++ = clip.get_top();
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	*ptr++ = x; *ptr++ = y + h;
	*ptr++ = clip.get_left(); *ptr++ = clip.get_bottom();
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	*ptr++ = x + w; *ptr++ = y + h;
	*ptr++ = clip.get_right(); *ptr++ = clip.get_bottom();
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	if (rotation != 0.0f)
		rotate_vertices(8, p, ptr, rotation, position);

	num_sprites++;
}

void SpriteBatch::draw(const glm::vec2& position, const glm::vec4& color, const glm::vec2& size, float rotation, const glm::vec2& origin) {
	if (current_tex) {
		render_batch();
		current_tex = nullptr;
	}

	if (ptr + 6 * 4 >= vertex_data.end())
		render_batch();

	float x = position.x - origin.x * size.x;
	float y = position.y - origin.y * size.x;
	float w = size.x;
	float h = size.y;

	float *p = ptr;
	*ptr++ = x; *ptr++ = y;
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	*ptr++ = x + w; *ptr++ = y;
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	*ptr++ = x; *ptr++ = y + h;
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	*ptr++ = x + w; *ptr++ = y + h;
	*ptr++ = color.r; *ptr++ = color.g; *ptr++ = color.b; *ptr++ = color.a;

	if (rotation != 0.0f)
		rotate_vertices(6, p, ptr, rotation, position);

	num_sprites++;
}

template <typename T, typename P>
void SpriteBatch::_impl_draw_string(const Font& font, T str, glm::vec2 position, P pred) {
	if (pred(str)) return;
	float sx = position.x;
	float h = font.impl->get_height();
	st_char c = (st_char)*str;
	if (c != '\n')
		font.impl->set_char(c);
	impl::FontChar fc;
	bool nl;
	while (true) {
		if (nl = (c == '\n')) {
			position.y += h;
			position.x = sx;
		} else {
			font.impl->get_char_info(fc);
			draw(fc.texture, position + fc.offset, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f), 0.0f, glm::vec2(0.0f, 0.0f), fc.bounds);
		}
		++str;
		if (pred(str))
			return;
		c = (st_char)*str;
		float f = font.impl->move_next(c);
		if (!nl)
			position.x += f;
	}
}

template <typename T>
void SpriteBatch::draw_string(const Font& font, const std::basic_string<T>& str, const glm::vec2& position) {
	_impl_draw_string(font, str.cbegin(), position, [&](const std::basic_string<T>::const_iterator& it) { return it == str.cend(); });
}

void SpriteBatch::draw_string(const Font& font, const st_char* str, const glm::vec2& position) {
	_impl_draw_string(font, str, position, [](const st_char* s){ return !s || *s == 0; });
}

void SpriteBatch::draw_string(const Font& font, const char* str, const glm::vec2& position) {
	_impl_draw_string(font, str, position, [](const char* s){ return !s || *s == 0; });
}

void SpriteBatch::draw_string(const Font& font, const st_string_utf8& str, const glm::vec2& position) {
	st_utf8_iterator end = str.end();
	_impl_draw_string(font, str.begin(), position, [&](const st_utf8_iterator& i){ return !i || i == end; });
}

void SpriteBatch::draw_string(const Font& font, const st_utf8_iterator& begin, const st_utf8_iterator& end, const glm::vec2& position) {
	_impl_draw_string(font, begin, position, [&](const st_utf8_iterator& i){ return !i || i == end; });
}

void SpriteBatch::end() {
	COLD_ASSERT(begun);
	begun = false;
	if (num_sprites != 0)
		render_batch();
}

void SpriteBatch::apply_shader(const Texture* tex, const glm::mat4& t) {
	Shader* s;
	if (tex) {
		shader.uniforms["t"] = *tex;
		s = &shader;
	} else
		s = &shader_no_tex;
	s->uniforms["w"] = t;
	s->apply();
	blend_state.apply();
}

void SpriteBatch::render_batch() { COLD_RENDER_DEBUG
	if (num_sprites == 0) return;
	apply_shader(current_tex, transform);
	if (current_tex == nullptr)
		vert_decl_no_tex.apply(vertex_data.begin());
	else
		vert_decl.apply(vertex_data.begin());
	index_buffer.apply();
	index_buffer.draw(DRAW_TRIANGLES, num_sprites * 2 * 3);

	num_sprites = 0;
	ptr = vertex_data.begin();
}

template void SpriteBatch::draw_string<char>(const Font&, const std::basic_string<char>&, const glm::vec2&);
template void SpriteBatch::draw_string<st_char>(const Font&, const std::basic_string<st_char>&, const glm::vec2&);

}