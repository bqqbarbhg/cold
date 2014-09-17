#ifndef _COLD_PLATFORM_STRING_H
#define _COLD_PLATFORM_STRING_H

#include <cold/util/assert.h>
#include <cstdint>
#include <string>

typedef std::uint32_t st_char;
typedef std::basic_string<st_char> st_string;
typedef unsigned char st_utf8_char;

unsigned int st_utf8_char_len(const st_utf8_char p);
unsigned int st_utf32_char_len(st_char c);
st_char st_utf8_decode(const st_utf8_char* p);
st_char st_utf8_decode(const st_utf8_char* p, unsigned int len);
st_utf8_char* st_utf8_encode(st_utf8_char* dest, st_char src);
void st_utf8_encode(st_utf8_char* dest, st_char src, unsigned int len);
inline bool st_utf8_is_valid(st_utf8_char c) {
	return (c & 0xC0) != 0x80;
}

struct st_utf8_iterator {
public:
	st_utf8_iterator() : ptr(nullptr) { }
	explicit st_utf8_iterator(st_utf8_char* p) : ptr(p) { }
	st_char operator*() const {
		COLD_DEBUG_ASSERT(ptr != nullptr);
		return st_utf8_decode(ptr);
	}
	st_utf8_char* get_ptr() const { return ptr; }
	void operator++() {
		ptr += st_utf8_char_len(*ptr);
	}
	void operator--() {
		ptr--;
		while (!st_utf8_is_valid(*ptr))
			ptr--;
	}
	void operator++(int) { operator++(); }
	void operator--(int) { operator--(); }
	bool operator<(const st_utf8_iterator& i) const { return ptr < i.ptr; }
	bool operator>(const st_utf8_iterator& i) const { return ptr < i.ptr; }
	bool operator<=(const st_utf8_iterator& i) const { return ptr <= i.ptr; }
	bool operator>=(const st_utf8_iterator& i) const { return ptr >= i.ptr; }

	st_utf8_iterator& operator+=(int i) {
		if (i < 0) return operator-=(-i);
		while (i--) operator++();
		return *this;
	}
	st_utf8_iterator& operator-=(int i) {
		if (i < 0) return operator+=(-i);
		while (i--) operator--();
		return *this;
	}
	st_utf8_iterator operator +(int i) const {
		st_utf8_iterator c = *this;
		c += i;
		return c;
	}
	st_utf8_iterator operator -(int i) const {
		st_utf8_iterator c = *this;
		c -= i;
		return c;
	}
	st_utf8_char operator[](int i) {
		return *(this + i);
	}
	int operator -(const st_utf8_iterator& i) {
		int r = 0;
		if (i < *this) {
			st_utf8_iterator c = i;
			while (c != *this) c++, r++;
		} else {
			st_utf8_iterator c = *this;
			while (c != i) c++, r--;
		}
		return r;
	}
	bool operator==(const st_utf8_iterator& i) const { return ptr == i.ptr; }
	bool operator!=(const st_utf8_iterator& i) const { return ptr != i.ptr; }

	operator bool() const { return ptr != nullptr; }

private:
	st_utf8_char* ptr;
};
class st_string_utf8 {
public:
	st_string_utf8() : buffer(nullptr), length(0), size(0) { }
	st_string_utf8(const st_char* ptr);
	st_string_utf8(const char* ptr);
	st_string_utf8(unsigned int length);
	~st_string_utf8();
	st_string_utf8(const st_string_utf8& s);
	st_string_utf8(st_string_utf8&& s);
	st_string_utf8& operator=(st_string_utf8 s);
	st_utf8_iterator begin() const { return st_utf8_iterator(buffer); }
	st_utf8_iterator end() const { return st_utf8_iterator(buffer + length); }
	void erase(const st_utf8_iterator& it);
	st_string_utf8& operator+=(const st_string_utf8& s);
	st_string_utf8 operator+(const st_string_utf8& s) const;
	st_string_utf8& operator +=(st_char ch);
	st_string_utf8 operator+(st_char ch) const;
	bool empty() const { return length == 0; }
private:
	st_utf8_char *buffer;
	unsigned int length, size;
};


#endif