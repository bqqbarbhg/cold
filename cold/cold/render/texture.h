#ifndef _COLD_RENDER_TEXTURE_H
#define _COLD_RENDER_TEXTURE_H

#include <glm/glm.hpp>
#include <cold/render/enums.h>

namespace cold {

struct RawTexture;

// Class that holds a texture instance
// Non-copyable except from Texture::Uninitialized
class Texture {
public:
	enum LoadFlags {
		// None
		NONE = 0,
		// Generate mipmaps
		GEN_MIPMAPS = 1 << 0,
		// Invert the Y axis
		INVERT_Y = 1 << 1,
		// Generate DXT compression
		GEN_DXT = 1 << 2,
		// Repeating texture
		REPEAT = 1 << 3,
	};

	Texture(const Texture& t);
	Texture(Texture&& t);
	Texture& operator=(Texture&& t);
	~Texture();

	// Sets the filtering mode for the texture
	// min: Minifying filter
	// mag: Magnifying filter
	// mip: Mipmap filter
	void set_filtering(TextureFiltering min, TextureFiltering mag, TextureFiltering mip);

	// Applies the texture to the current render state
	// TODO(bqq): Multiple textures
	void apply() const;

	// Returns the width of the texture in pixels
	int get_width() const { return width; }

	// Returns the width of the texture in pixels
	int get_height() const { return height; }

	// Returns the origin of the texture (half of the size)
	glm::vec2 get_origin() const { return glm::vec2(width, height) * 0.5f; }

	// Returns the size of the texture
	glm::vec2 get_size() const { return glm::vec2(width, height); }

	// Loads a texture from a file
	// file: Name of the file to be load
	// flags: Flags to use while loading the image
	static Texture load_file(const char* file, LoadFlags flags=NONE);

	// Loads a texture from a RawTexture
	// Uses and invalidates the RawTexture `r`
	// r: Raw texture handle to load the image from
	// flags: Flags to use while loading the image
	static Texture load(RawTexture &&r, LoadFlags flags=NONE);


	static Texture Uninitialized;

	bool operator==(const Texture& o) const { return gl_texture == o.gl_texture; }
	bool operator!=(const Texture& o) const { return gl_texture != o.gl_texture; }
private:
	friend class Shader;
	Texture(unsigned int id, int w, int h);
	unsigned int gl_texture;
	int width, height;
};

}

#endif