#include "text_resource_loader.h"
#include <cold/resource/load_info.h>
#include <cold/resource/text_resource_parser.h>
#include <cold/resource/raw_texture.h>
#include <cold/platform/io.h>
#include <soil/SOIL.h>
#include <iostream>
#include <fstream>
#include <cold/resource/file_handle.h>
#include <cold/render/font/fnt_font.h>
#include <cold/util/unique_ptr.h>

namespace cold {

namespace {
void free_fn(unsigned char* c) {
	SOIL_free_image_data(c);
}
}

bool TextResourceLoader::load(ResourceLoadInfo& info, const std::string& name) {
	std::ifstream stream(root + name + ".crs");
	if (!stream.good()) return false;
	TextResourceParser parse(stream);
	if (!parse.parse(info))
		return false;
	return true;
}

RawTexture TextResourceLoader::load_texture(const std::string& name) {
	RawTexture r(free_fn);
	r.data = SOIL_load_image((root + name).c_str(), &r.width, &r.height, &r.channels, SOIL_LOAD_AUTO);
	return r;
}

FileHandle TextResourceLoader::load_file(const std::string& name) {
	return FileHandle::load_file((root + name).c_str());
}

std::string TextResourceLoader::load_string(const std::string& name) {
	return read_file_string((root + name).c_str());
}

std::istream* TextResourceLoader::load_stream(const std::string& name) {
	return new std::ifstream(root + name);
}
impl::FntFont* TextResourceLoader::load_fnt(const std::string& name) {
	UniquePtr<impl::FntFont> f = new impl::FntFont();
	f->load_text_fnt(name);
	return f.release();
}

}