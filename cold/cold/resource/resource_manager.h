#ifndef _COLD_RESOURCE_RESOURCE_MANAGER_H
#define _COLD_RESOURCE_RESOURCE_MANAGER_H

#include <cold/resource/handle.h>
#include <cold/resource/resource_loader.h>
#include <cold/resource/resource.h>
#include <cold/util/unique_ptr.h>
#include <cold/resource/load_info.h>
#include <unordered_map>
#include <string>

namespace cold {

template <class T>
class ResourceManager {
public:
	static Handle<T> get(const std::string& s) {
		auto it = resources.find(s);
		if (it != resources.end()) {
			return Handle<T>(it->second);
		} else {
			// TODO(bqq): Handle errors
			ResourceLoadInfo info;
			bool loaded = ResourceLoader::get()->load(info, s);
			COLD_DEBUG_ASSERT(loaded);
			Resource<T>* t = Resource<T>::load(info);
			COLD_DEBUG_ASSERT(t != 0);
			return Handle<T>(resources[s] = t);
		}
	}
private:
	static std::unordered_map<std::string, UniquePtr<Resource<T>>> resources;
};

template <class T>
std::unordered_map<std::string, UniquePtr<Resource<T>>> ResourceManager<T>::resources;

}

#endif