#ifndef _COLD_UTIL_EITHER_H
#define _COLD_UTIL_EITHER_H

#include <utility>
#include <cold/util/assert.h>
#include <new>

template <typename T, typename U>
class Either {
public:
	Either(const Either<T, U>& tu) : _is_t(tu._is_t) { 
		if (_is_t)
			new (data) T(reinterpret_cast<T>(tu.data));
		else
			new (data) U(reinterpret_cast<U>(tu.data));	
	}
	Either(const T& t) : _is_t(true) { new (data) T(t); }
	Either(const U& u) : _is_t(false) { new (data) U(u); }
	
	Either(Either<T, U>&& tu) : _is_t(tu._is_t) {
		if (_is_t)
			new (data) T(std::move(reinterpret_cast<T>(tu.data)));
		else
			new (data) U(std::move(reinterpret_cast<U>(tu.data)));
	}
	Either(T&& t) : _is_t(true) { new (data) T(std::forward<T>(t)); }
	Either(U&& u) : _is_t(false) { new (data) U(std::forward<U>(u)); }
	
	Either<T, U>& operator= (const Either<T, U>& tu) {
		if (_is_t && tu._is_t && *(T*)data == *(T*)tu.data) return;
		if (!_is_t && !tu._is_t && *(U*)data == *(U*)tu.data) return;
		_assign(tu._is_t);
		if (_is_t)
			new (data) T(reinterpret_cast<T>(tu.data));
		else
			new (data) U(reinterpret_cast<U>(tu.data));	
		return *this;
	}
	Either<T, U>& operator= (const T& t) {
		if (_is_t && *(T*)data == t) return;
		_assign(true);
		new (data) T(t);
		return *this;
	}
	Either<T, U>& operator= (const U& u) {
		if (!_is_t && *(U*)data == t) return;
		_assign(false);
		new (data) U(u);
		return *this;
	}
	Either<T, U>& operator= (Either<T, U>&& tu) {
		_assign(tu._is_t);
		if (_is_t)
			new (data) T(std::move(reinterpret_cast<T>(tu.data)));
		else
			new (data) U(std::move(reinterpret_cast<U>(tu.data)));
		return *this;
	}
	Either<T, U>& operator= (T&& t) {
		_assign(true);
		new (data) T(std::forward(t));
		return *this;
	}
	Either<T, U>& operator= (U&& t) {
		_assign(false);
		new (data) U(std::forward(t));
		return *this;
	}

	bool is_first() const { return _is_t; }
	bool is_second() const { return !_is_t; }
	T& get_first() { return reinterpret_cast<T>(tu.data); }
	U& get_second() { return reinterpret_cast<U>(tu.data); }

private:
	inline void _assign(bool t) {
		if (_is_t)
			reinterpret_cast<T>(data)->~T();
		else
			reinterpret_cast<U>(data)->~U();
		_is_t = t;
	}
	char data[sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U)];
	bool _is_t;
};

#endif