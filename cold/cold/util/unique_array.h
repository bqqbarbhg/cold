#ifndef _COLD_UTIL_UNIQUE_ARRAY_H
#define _COLD_UTIL_UNIQUE_ARRAY_H

#include <cold/util/assert.h>

template <typename T>
class UniqueArray {
public:
	UniqueArray() : t(nullptr), e(nullptr) { }
	UniqueArray(unsigned int length) : t(new T[length]) { e = t + length; }
	UniqueArray(UniqueArray<T>&& a)
		: t(a.t), e(a.e)
	{
		a.t = nullptr;
	}
	UniqueArray& operator=(UniqueArray<T>&& a) {
		e = a.e;
		if (t == a.t)
			return *this;	
		delete[] t;
		t = a.t;
		a.t = nullptr;
		return *this;
	}
	~UniqueArray() {
		delete[] t;
	}
	T& operator[] (unsigned int i) {
		COLD_DEBUG_ASSERT(t != nullptr);
		COLD_DEBUG_ASSERT(i < (unsigned int)(e - t));
		return t[i];
	}
	T* begin() const { return t; }
	T* end() const { return e; }
	unsigned int size() const { return e - t; }
private:
	UniqueArray(const UniqueArray<T>& p);
	UniqueArray& operator=(const UniqueArray<T>& p);
	T *t, *e;
};

#endif