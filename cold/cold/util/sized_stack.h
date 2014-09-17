#ifndef _COLD_UTIL_SIZED_STACK_H
#define _COLD_UTIL_SIZED_STACK_H

#include <algorithm>

template <typename T>
class SizedStack {
public:
	SizedStack()
		: data(nullptr)
	{
	}
	SizedStack(unsigned int size)
		: data(new T[size])
	{
		eptr = (dptr = data) + size;
	}
	SizedStack(const SizedStack& s)
	{
		eptr = (data = new T[s.eptr - s.data]) + (s.eptr - s.data);
		dptr = data + (s.dptr - s.data);
		for (T *dst = data, *src = s.data; dst != eptr;)
			*dst++ = *src++;
	}
	SizedStack(SizedStack&& s)
		: data(s.data), dptr(s.dptr), eptr(s.eptr)
	{
		s.data = nullptr;
	}
	SizedStack<T>& operator=(SizedStack<T> rhs) {
		std::swap(data, rhs.data);
		std::swap(dptr, rhs.dptr);
		std::swap(eptr, rhs.eptr);
		return *this;
	}
	~SizedStack() {
		delete[] data;
	}
	T* begin() { return data; }
	T* end() { return dptr; }
	const T* cbegin() const { return data; }
	const T* cend() const { return dptr; }
	unsigned int count() const { return dptr - data; }
	unsigned int size() const { return eptr - data; }
	bool empty() const { return dptr == data; }
	bool push(const T& t) {
		if (dptr == eptr) return true;
		*dptr++ = t;
		return false;
	}
	T pop() {
		return *--dptr;
	}
private:
	T *data, *dptr, *eptr;
};


#endif