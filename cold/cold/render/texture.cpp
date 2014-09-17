#include "texture.h"
#include <cold/render/impl/gl.h>
#include <soil/SOIL.h>
#include <cold/util/assert.h>
#include <cold/resource/raw_texture.h>
#include <cold/resource/resource_loader.h>
#include <cold/resource/resource.h>
#include <cold/resource/load_info.h>

namespace cold {

Texture Texture::Uninitialized = Texture(0, 0, 0);

Texture::Texture(const Texture& t)
	: gl_texture(0)
{
	COLD_DEBUG_ASSERT(&t == &Uninitialized);
}
Texture::Texture(Texture &&t)
	: width(t.width), height(t.height), gl_texture(t.gl_texture)
{
	COLD_DEBUG_ASSERT(t.gl_texture != 0);
	gl_texture = t.gl_texture;
	t.gl_texture = 0;
}
Texture& Texture::operator=(Texture&& t) {
	if (gl_texture == t.gl_texture) return *this;
	width = t.width;
	height = t.height;
	gl_texture = t.gl_texture;
	t.gl_texture = 0;
	return *this;
}
Texture::Texture(unsigned int i, int w, int h)
	: gl_texture(i), width(w), height(h)
{
}

Texture::~Texture() {
	if (gl_texture != 0)
		glDeleteTextures(1, &gl_texture);
}

void Texture::apply() const {
	glBindTexture(GL_TEXTURE_2D, gl_texture);
}

Texture Texture::load(RawTexture&& t, LoadFlags flags) {
	unsigned int soilf = 0;
	if (flags & GEN_MIPMAPS) soilf |= SOIL_FLAG_MIPMAPS;
	if (flags & INVERT_Y) soilf |= SOIL_FLAG_INVERT_Y;
	if (flags & GEN_DXT) soilf |= SOIL_FLAG_COMPRESS_TO_DXT;
	if (flags & REPEAT) soilf |= SOIL_FLAG_TEXTURE_REPEATS;

	return Texture(SOIL_create_OGL_texture(t.data, t.width, t.height, t.channels, SOIL_CREATE_NEW_ID, soilf), t.width, t.height);
}
Texture Texture::load_file(const char* file, LoadFlags flags) {
	return Texture::load(ResourceLoader::get()->load_texture(file), flags);
}

void Texture::set_filtering(TextureFiltering min, TextureFiltering mag, TextureFiltering mip) {
	apply();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mip + ((mip == FILTER_NEAREST) ? 0x100 : 0x102));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

template <>
Resource<Texture>* Resource<Texture>::load(const ResourceLoadInfo& info) {
	std::string s;
	if (!info.get_arg("source", s)) return nullptr;
	Texture::LoadFlags lf = Texture::REPEAT;
	if (info.get_flag("gen-mipmaps")) lf = (Texture::LoadFlags)(lf | Texture::GEN_MIPMAPS);
	if (info.get_flag("invert-y")) lf = (Texture::LoadFlags)(lf | Texture::INVERT_Y);
	if (info.get_flag("gen-dxt")) lf = (Texture::LoadFlags)(lf | Texture::GEN_DXT);
	if (info.get_flag("clamp")) lf = (Texture::LoadFlags)(lf & ~Texture::REPEAT);
	return new Resource<Texture>(Texture::load(ResourceLoader::get()->load_texture(s), lf));
}

}