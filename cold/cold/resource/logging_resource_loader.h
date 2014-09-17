#ifndef _COLD_RESOURCE_LOGGING_RESOURCE_LOADER_H
#define _COLD_RESOURCE_LOGGING_RESOURCE_LOADER_H

#include <cold/resource/resource_loader.h>
#include <cold/util/unique_ptr.h>
#include <iostream>

namespace cold {

class LoggingResourceLoader : public ResourceLoader {
public:
	LoggingResourceLoader(UniquePtr<ResourceLoader>&& in, std::ostream&);
	virtual bool load(ResourceLoadInfo& i, const std::string& name);
	virtual RawTexture load_texture(const std::string& name);
	virtual FileHandle load_file(const std::string& name);
	virtual std::istream* load_stream(const std::string& name);
	virtual impl::FntFont* load_fnt(const std::string& name);
	std::string load_string(const std::string& name);
private:
	UniquePtr<ResourceLoader> inner;
	std::ostream& out;
};

}

#endif