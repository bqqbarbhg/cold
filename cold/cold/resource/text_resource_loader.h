#ifndef _COLD_RESOURCE_TEXT_RESOURCE_LOADER_H
#define _COLD_RESOURCE_TEXT_RESOURCE_LOADER_H

#include <cold/resource/resource_loader.h>

namespace cold {

class TextResourceLoader : public ResourceLoader {
public:
	TextResourceLoader(const std::string& root)
		: root(root)
	{
	}

	virtual bool load(ResourceLoadInfo &i, const std::string& name);
	virtual RawTexture load_texture(const std::string& name);
	virtual FileHandle load_file(const std::string& name);
	virtual std::istream* load_stream(const std::string& name);
	virtual impl::FntFont* load_fnt(const std::string& name);
	virtual std::string load_string(const std::string& name);
private:
	std::string root;
};

}

#endif