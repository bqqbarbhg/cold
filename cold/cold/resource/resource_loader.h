#ifndef _COLD_RESOURCE_RESOURCE_LOADER_H
#define _COLD_RESOURCE_RESOURCE_LOADER_H

#include <istream>
#include <string>

namespace cold {

struct RawTexture;
struct ResourceLoadInfo;
struct FileHandle;
namespace impl { class FntFont; }
class ResourceLoader {
public:
	static ResourceLoader *get() { return loader; }
	static void provide(ResourceLoader* r) { loader = r; }
	virtual bool load(ResourceLoadInfo& i, const std::string& name) = 0;
	virtual RawTexture load_texture(const std::string& name) = 0;
	virtual FileHandle load_file(const std::string& name) = 0;
	virtual std::istream* load_stream(const std::string& name) = 0;
	virtual impl::FntFont* load_fnt(const std::string& name) = 0;
	virtual std::string load_string(const std::string& name) = 0;
private:
	static ResourceLoader* loader;
};

}

#endif