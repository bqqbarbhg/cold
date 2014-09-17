#ifndef _COLD_UTIL_COUNT_VECTOR_H
#define _COLD_UTIL_COUNT_VECTOR_H

#include <cold/util/raw_vector.h>

namespace cold {

class CountVector : private RawVector {
public:
	CountVector(unsigned int el_size);
	CountVector(const CountVector& v);
	CountVector& operator=(CountVector rhs);

	template <typename T>
	void add(const T& t) {
		count++;
		*push<T>(elem_size) = t;
	}
	inline void* get_mutable_pointer() { return RawVector::get_mutable_pointer(); }
	inline const void* get_pointer() const { return RawVector::get_pointer(); }
	inline unsigned int get_size() const { return RawVector::get_size(); }
	inline unsigned int get_count() const { return count; }
	/*template <typename T>
	inline T& get(unsigned int index) const { return _data + index * elem_size; }*/
private:
	unsigned int count, elem_size;
};

}

#endif