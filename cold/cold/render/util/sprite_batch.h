#ifndef _COLD_RENDER_UTIL_SPRITE_BATCH_H
#define _COLD_RENDER_UTIL_SPRITE_BATCH_H

#include <cold/render/index_buffer.h>
#include <cold/render/enums.h>
#include <cold/util/unique_array.h>
#include <cold/math/rectangle.h>
#include <cold/render/blend_state.h>
#include <cold/util/string.h>

#include <glm/glm.hpp>
#include <string>

namespace cold {

class Texture;
class Font;
class Shader;
class VertexDeclaration;
struct VertexElement;

// Tool to draw sprites in batches
class SpriteBatch {
public:
	SpriteBatch(unsigned int max_batch);
	~SpriteBatch();

	// Begin sprite batching
	// Must be called before any draw function is called
	// blend: Blend state to render the sprites with
	void begin(const BlendState& blend = BlendState::AlphaBlend);


	void draw(
		const Texture& texture,
		const glm::vec2& position,
		const glm::vec4& color = glm::vec4(1.0f),
		const glm::vec2& size = glm::vec2(1.0f),
		float rotation = 0.0f,
		const glm::vec2& origin = glm::vec2(0.0f),
		const Rectangle& clip = Rectangle::Unit
		);
	void draw(
		const glm::vec2& position,
		const glm::vec4& color = glm::vec4(1.0f),
		const glm::vec2& size = glm::vec2(1.0f),
		float rotation = 0.0f,
		const glm::vec2& origin = glm::vec2(0.0f)
		);
	void draw_string(const Font& font, const char* str, const glm::vec2& position);
	void draw_string(const Font& font, const st_char* str, const glm::vec2& position);
	void draw_string(const Font& font, const st_string_utf8& str, const glm::vec2& position);
	template <typename T>
	void draw_string(const Font& font, const std::basic_string<T>& str, const glm::vec2& position);
	void draw_string(const Font& font, const st_utf8_iterator& begin, const st_utf8_iterator& end, const glm::vec2& position);

	// End sprite batching
	// Renders unrendred batched sprites
	void end();

	// Force a batch render
	void render_batch();

	// Sets the bounds for the rendering area
	// bounds: Bounds to set
	void set_bounds(const Rectangle& bounds);

	// Applies the shader
	// If called outside SpriteBatch `render_batch` should be called before rendering anything
	// tex: Pointer to a texture to use with the shader or nullptr to render solid quads
	// transform: Matrix to use with the rendering (usually get_transform())
	void apply_shader(const Texture* tex, const glm::mat4& transform);

	// Gets the transform of the sprite batch
	glm::mat4 get_transform() const { return transform; }

	// Vertex declaration of all textured sprites
	static const VertexDeclaration vert_decl;

	// Vertex declaration of all non-textured sprites
	static const VertexDeclaration vert_decl_no_tex;
private:
	template <typename T, typename P>
	void _impl_draw_string(const Font& font, T str, glm::vec2 position, P pred);
	SpriteBatch(const SpriteBatch& b);
	SpriteBatch& operator=(const SpriteBatch& b);
	IndexBuffer index_buffer;
	UniqueArray<float> vertex_data;
	const Texture* current_tex;
	glm::mat4 transform;
	float* ptr;
	unsigned int num_sprites;
	bool begun;
	BlendState blend_state;

	static void initialize();
	static bool initialized;
	static const char *vert_shader, *frag_shader, *vert_shader_no_tex, *frag_shader_no_tex;
	static Shader shader, shader_no_tex;
	static const VertexElement vert_elems[], vert_elems_no_tex[];
};

}

#endif