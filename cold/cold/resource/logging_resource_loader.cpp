#include "logging_resource_loader.h"
#include <cold/resource/raw_texture.h>
#include <cold/resource/file_handle.h>

namespace cold {

LoggingResourceLoader::LoggingResourceLoader(UniquePtr<ResourceLoader>&& in, std::ostream& o)
	: inner(std::forward<UniquePtr<ResourceLoader>>(in)), out(o)
{
}

bool LoggingResourceLoader::load(ResourceLoadInfo& i, const std::string& name) {
	out << "Loading resource '" << name << "'\n";
	return inner->load(i, name);
}
RawTexture LoggingResourceLoader::load_texture(const std::string& name) {
	out << "Loading texture '" << name << "'\n";
	return inner->load_texture(name);
}
FileHandle LoggingResourceLoader::load_file(const std::string& name) {
	out << "Loading file '" << name << "'\n";
	return inner->load_file(name);
}
std::string LoggingResourceLoader::load_string(const std::string& name) {
	out << "Loading string '" << name << "'\n";
	return inner->load_string(name);
}
std::istream* LoggingResourceLoader::load_stream(const std::string& name) {
	out << "Loading stream '" << name << "'\n";
	return inner->load_stream(name);
}
impl::FntFont* LoggingResourceLoader::load_fnt(const std::string& name) {
	out << "Loading font '" << name << "'\n";
	return inner->load_fnt(name);
}

}