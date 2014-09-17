#ifndef _COLD_RESOURCE_RESOURCE_H
#define _COLD_RESOURCE_RESOURCE_H

#include <utility>

namespace cold {
struct ResourceLoadInfo;
template <class T>
struct Resource {
	explicit Resource(T&& t)
		: resource(std::forward<T>(t)), ref_count(0)
	{
	}
	Resource(Resource&& r)
		: resource(std::move(r.resource)), ref_count(r.ref_count)
	{
	}
	static Resource<T>* load(const ResourceLoadInfo& info);

	T resource;
	unsigned int ref_count;
};
}

#endif