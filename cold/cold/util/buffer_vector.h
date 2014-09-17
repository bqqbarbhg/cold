#ifndef _COLD_UTIL_BUFFER_VECTOR_H
#define _COLD_UTIL_BUFFER_VECTOR_H
#include <cstdlib>
#include <cstring>
#include <algorithm>

class BufferVector {
public:
	BufferVector(unsigned int element_size) : _elem_size(element_size), _buffer(nullptr), _count(0), _capacity(0) {
	}
	BufferVector(const BufferVector& b) : _count(b._count), _capacity(b._capacity), _elem_size(b._elem_size) {
		unsigned int sz = _count * _elem_size;
		_buffer = (char*)std::malloc(sz);
		std::memcpy(_buffer, b._buffer, sz);
	}
	BufferVector(BufferVector&& b) : _count(b._count), _capacity(b._capacity), _elem_size(b._elem_size), _buffer(b._buffer) {
		b._buffer = nullptr;
	}
	~BufferVector() {
		std::free(_buffer);
	}

	BufferVector& operator=(BufferVector bv) {
		std::swap(_buffer, bv._buffer);
		_count = bv._count;
		_capacity = bv._capacity;
		_elem_size = bv._elem_size;
		return *this;
	}

	// Reserve elements (does not increase count)
	// count: How many elements to reserve
	void reserve(unsigned int count) {
		_buffer = (char*)std::realloc(_buffer, count * _elem_size);
	}
	void push_back_raw(const void* ptr) {
		if (_count + 1 > _capacity) {
			reserve(_capacity = (_capacity << 1) + 1);
		}
		std::memcpy(_buffer + _count * _elem_size, ptr, _elem_size);
		_count++;
	}
	// Push back an element
	// t: Element to be pushed back
	template <typename T>
	void push_back(const T& t) {
		push_back_raw(&t);
	}

	// Returns the count of the vector's contents
	unsigned int get_count() const { return _count; }

	// Returns the size of the vector's contents in bytes
	unsigned int get_size() const { return _count * _elem_size; }

	// Returns a pointer to the elements
	void* get_pointer() const { return _buffer; }

	template <typename T>
	T& get(unsigned int index) const {
		return *(T*)(_buffer + _elem_size * index);
	}

	template <typename T>
	struct Iterator
		: public std::iterator<std::forward_iterator_tag, T> {
		Iterator(BufferVector *v, unsigned int i)
			: vec(v), index(i) { }
		T& operator*() { return vec->get<T>(index); }
		void operator++() { index++; }
		void operator++(int) { index++; }
		bool operator==(const Iterator<T>& i) const { return index == i.index; }
		bool operator!=(const Iterator<T>& i) const { return !(*this == i); }
	private:
		BufferVector *vec;
		unsigned int index;
	};

	template <typename T>
	Iterator<T> begin() { return Iterator<T>(this, 0); }
	template <typename T>
	Iterator<T> end() { return Iterator<T>(this, _count); }
private:
	char *_buffer;
	unsigned int _count, _capacity;
	unsigned int _elem_size;
};

#endif