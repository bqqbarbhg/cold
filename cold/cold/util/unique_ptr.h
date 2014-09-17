#ifndef _COLD_UTIL_UNIQUE_PTR_H
#define _COLD_UTIL_UNIQUE_PTR_H

template <typename T>
class UniquePtr {
public:
	UniquePtr() : t(nullptr) { }
	UniquePtr(T* ptr) : t(ptr) { }
	UniquePtr(UniquePtr<T>&& p)
		: t(p.t)
	{
		p.t = nullptr;
	}
	UniquePtr& operator=(UniquePtr<T>&& p) {
		if (t == p.t) return *this;
		delete t;
		t = p.t;
		p.t = nullptr;
		return *this;
	}
	~UniquePtr() {
		delete t;
	}
	T& operator*() const {
		return *t;
	}
	T* operator->() const {
		return t;
	}
	operator T*() const {
		return t;
	}
	T* release() {
		T* w = t;
		t = nullptr;
		return w;
	}
private:
	UniquePtr(const UniquePtr<T>& p);
	UniquePtr& operator=(const UniquePtr<T>& p);
	T* t;
};

#endif