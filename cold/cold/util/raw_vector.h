#ifndef _COLD_UTIL_RAW_VECTOR_H
#define _COLD_UTIL_RAW_VECTOR_H

namespace cold {

class RawVector {
public:
	RawVector(unsigned int s = 0);
	RawVector(const RawVector& v);
	~RawVector();
	RawVector& operator=(RawVector rhs);

	void reserve(unsigned int len);
	template <typename T>
	T *push(unsigned int size) {
		unsigned int os = _size;
		reserve(size);
		return get<T>(os);
	}

	template <class T>
	T *get(unsigned int index) {
		return reinterpret_cast<T*>(_data + index);
	}
	template <class T>
	const T *get_const(unsigned int index) const {
		return reinterpret_cast<const T*>(_data + index);
	}

	inline unsigned int get_size() const { return _size; }
	inline void* get_mutable_pointer() { return _data; }
	inline const void* get_pointer() const { return _data; }
private:
	unsigned int _size;
	char *_data;
};

}

#endif