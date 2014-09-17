#ifndef _COLD_UTIL_MAYBE_H
#define _COLD_UTIL_MAYBE_H

#include <new>
#include <utility>
#include <type_traits>

enum _maybe_noval_t {
	Nothing = 0xdeadbeef
};

template <typename T>
class Maybe {
public:
	Maybe() : _is(false) { }
	Maybe(const _maybe_noval_t& n) : _is(false) { }
	Maybe(const T& t) : _is(true) { new (_data)T(t); }
	Maybe(T&& t) : _is(true) { new (_data)T(std::move(t)); }
	Maybe(const Maybe<T>& m) : _is(m._is) { if (_is) new (_data)T(*(const T*)m._data); }
	Maybe(Maybe<T>&& m) : _is(m._is) { if (_is) new (_data)T(std::move(*(T*)m._data)); m._is = false; }
	~Maybe() {
		if (_is) ((T*)_data)->~T();
	}

	Maybe<T>& operator=(const _maybe_noval_t&) {
		if (_is) ((T*)_data)->~T();
		_is = false;
	}
	Maybe<T>& operator=(const T& t) {
		if (_is) ((T*)_data)->~T();
		_is = true;
		new (_data)T(t);
		return *this;
	}
	Maybe<T>& operator=(T&& t) {
		if (_is) ((T*)_data)->~T();
		_is = true;
		new (_data)T(std::move(t));
		return *this;
	}
	Maybe<T> operator=(const Maybe<T>& m) {
		if (&m == this)
			return *this;
		if (_is) ((T*)_data)->~T();
		if (_is = m._is) new (_data)T(*(const T*)m._data);
		return *this;
	}
	Maybe<T> operator=(Maybe<T>&& m) {
		if (&m == this)
			return *this;
		if (_is) ((T*)_data)->~T();
		if (_is = m._is) new (_data)T(std::move(*(T*)m._data));
		m._is = false;
		return *this;
	}

	bool operator==(const Maybe<T>& m) const {
		if (_is != m._is)
			return false;
		if (_is)
			return *(T*)_data == *(T*)m._data;
		return true;
	}
	bool operator!=(const Maybe<T>& m) const {
		return !(*this == m);
	}

	T* operator->() const {
		return (T*)_data;
	}
	T& operator*() const {
		return *(T*)_data;
	}
	T& value() const {  return *(T*)_data; }
	bool has_value() const { return _is; }
private:
	bool _is;
	char _data[sizeof(T)];
};

#endif