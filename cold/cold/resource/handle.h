#ifndef _COLD_RESOURCE_HANDLE_H
#define _COLD_RESOURCE_HANDLE_H

#include <cold/resource/resource.h>
#include <cold/util/assert.h>

namespace cold {

template <class T>
class Handle {
public:
	Handle()
		: _res(nullptr)
	{
	}
	explicit Handle(Resource<T>* r)
		: _res(r)
	{
		if (_res)
			_res->ref_count++;
	}
	Handle(const Handle<T>& h)
		: _res(h._res)
	{
		if (_res)
			_res->ref_count++;
	}
	Handle& operator=(const Handle<T>& h) { 
		if (h._res == _res) return *this;
		if (_res)
			_res->ref_count--;
		_res = h._res;
		_res->ref_count++;
		return *this;
	}
	Handle(Handle<T>&& h)
		: _res(h._res)
	{
		h._res = nullptr;
	}
	Handle& operator=(Handle<T>&& h) {
		if (h._res == _res) return *this;
		if (_res)
			_res->ref_count--;
		_res = h._res;
		h._res = nullptr;
		return *this;
	}
	operator const T&() const {
		return _res->resource;
	}
	~Handle() {
		// TODO(bqq): Be not stupid
		if (_res && false)
			_res->ref_count--;
	}

	T& operator*() const {
		COLD_DEBUG_ASSERT(_res != nullptr);
		return _res->resource;
	}
	T* operator->() const {
		COLD_DEBUG_ASSERT(_res != nullptr);
		return &_res->resource;
	}
private:
	Resource<T>* _res;
};

}

#endif