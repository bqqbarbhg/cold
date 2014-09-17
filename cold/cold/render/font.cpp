#include "font.h"

#include <cold/resource/resource.h>
#include <cold/resource/load_info.h>
#include <cold/resource/resource_loader.h>
#include <cold/resource/resource_manager.h>
#include <cold/render/font/basic_ascii_font.h>
#include <utility>

namespace cold {

Font::Font(UniquePtr<impl::FontImpl>&& u)
	: impl(std::move(u))
{
}
Font::Font(Font&& f)
	: impl(std::move(f.impl))
{
}
Font &Font::operator=(Font&& f) {
	impl = std::move(f.impl);
	return *this;
}

template <>
Resource<Font>* Resource<Font>::load(const ResourceLoadInfo& info) {
	std::string s;
	if (info.get_arg("basic_ascii", s)) {
		Handle<Texture> t = ResourceManager<Texture>::get(s);
		// TODO(bqq): Error handling for resource handles
		return new Resource<Font>(Font(new impl::BasicASCIIFont(t)));
	} else if (info.get_arg("fnt", s)) {
		auto a = ResourceLoader::get()->load_fnt(s);
		return new Resource<Font>(Font((impl::FontImpl*)a));
	}
	return nullptr;
}

}