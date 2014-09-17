#include "string.h"
#include <cold/util/endian.h>

unsigned int st_utf8_char_len(const st_utf8_char p) {
	COLD_DEBUG_ASSERT(st_utf8_is_valid(p));
	st_utf8_char hi = 0x80;
	if ((p & hi) == 0) return 1;
	unsigned int s = 1;
	hi >>= 1;
	while (p & hi)
		s++, hi >>= 1;
	return s;
}
unsigned int st_utf32_char_len(st_char c) {
	if ((c & 0xFFFFFF80) == 0) return 1;
	if ((c & 0xFFFFF800) == 0) return 2;
	if ((c & 0xFFFF0000) == 0) return 3;
	COLD_DEBUG_ASSERT((c & 0xFFE00000) == 0);
	return 4;
}
st_char st_utf8_decode(const st_utf8_char* p) {
	COLD_DEBUG_ASSERT(st_utf8_is_valid(*p));
	st_utf8_char hi = 0x80, c = *p;
	if ((c & hi) == 0) return c;
	unsigned int s = 1;
	while ((hi >>= 1) & c) s++;
	st_char ch = (0xFF >> s) & (st_char)c;
	while (--s)
		ch = ch << 6 | *++p & 0x7F;
	return ch;
}
st_char st_utf8_decode(const st_utf8_char* p, unsigned int len) {
	COLD_DEBUG_ASSERT(st_utf8_is_valid(*p));
	st_char ch = (0xFF >> len) & (st_char)*p;
	while (--len) ch = ch << 6 | *++p & 0x7F;
	return ch;
}
void st_utf8_encode(st_utf8_char* dest, st_char src, unsigned int len) {
	if (len == 1) {
		*dest = (st_utf8_char)src;
	} else {
		st_utf8_char *c = dest + len;
		while (--c != dest) {
			*c = 0x80 | src & 0x3f;
			src >>= 6;
		}
		*c = 0xFF & ~(0xFF >> len) | src;
	}
}
st_utf8_char* st_utf8_encode(st_utf8_char* dest, st_char src) {
	unsigned int l = st_utf32_char_len(src);
	st_utf8_encode(dest, src, l);
	return dest + l;
}

st_string_utf8::st_string_utf8(unsigned int len)
	: length(len), size(len), buffer((st_utf8_char*)std::malloc(len))
{
}
st_string_utf8::st_string_utf8(const st_char* ptr) {
	COLD_DEBUG_ASSERT(ptr != 0);
	length = 0;
	const st_char* c = ptr;
	while (*c)
		length += st_utf32_char_len(*c++);
	size = length;
	if (length > 0) {
		buffer = (st_utf8_char*)std::malloc(length);
	} else {
		buffer = nullptr;
	}
}
st_string_utf8::st_string_utf8(const char* ptr) {
	COLD_DEBUG_ASSERT(ptr != 0);
	size = length = std::strlen(ptr);
	if (length > 0) {
		buffer = (st_utf8_char*)std::malloc(length);
		std::memcpy(buffer, ptr, length);
	} else {
		buffer = nullptr;
	}
}
st_string_utf8::~st_string_utf8() {
	if (buffer)
		free(buffer);
}
st_string_utf8::st_string_utf8(const st_string_utf8& s)
	: length(s.length), size(s.length)
{
	buffer = (st_utf8_char*)std::malloc(size);
	std::memcpy(buffer, s.buffer, length);
}
st_string_utf8::st_string_utf8(st_string_utf8&& s)
	: length(s.length), size(s.length), buffer(s.buffer)
{
	s.buffer = nullptr;
}
st_string_utf8& st_string_utf8::operator=(st_string_utf8 s) {
	std::swap(buffer, s.buffer);
	length = s.length;
	size = s.size;
	return *this;
}
void st_string_utf8::erase(const st_utf8_iterator& it) {
	COLD_DEBUG_ASSERT(length != 0);
	st_utf8_char* c = it.get_ptr();
	int l = st_utf8_char_len(*c);
	length -= l;
	if (it == end())
		return;
	std::memmove(c, c + l, end() - it);
}
st_string_utf8& st_string_utf8::operator+=(const st_string_utf8& s) {
	if (length + s.length > size) {
		size += s.length;
		buffer = (st_utf8_char*)std::realloc(buffer, size);
	}
	std::memcpy(buffer + length, s.buffer, s.length);
	length += s.length;
	return *this;
}
st_string_utf8 st_string_utf8::operator+(const st_string_utf8& s) const {
	st_string_utf8 c(length + s.length);
	std::memcpy(c.buffer, buffer, length);
	std::memcpy(c.buffer + length, s.buffer, s.length);
	return c;
}
st_string_utf8& st_string_utf8::operator+=(st_char ch) {
	unsigned int l = st_utf32_char_len(ch);
	if (length + l >= size) {
		if (size < 5)
			size = 5 + l;
		else
			size = size * 2 + l;
		buffer = (st_utf8_char*)std::realloc(buffer, size);
	}
	st_utf8_encode(buffer + length, ch, l);
	length += l;
	return *this;
}
st_string_utf8 st_string_utf8::operator+(st_char ch) const {
	unsigned int l = st_utf32_char_len(ch);
	st_string_utf8 c(length + l);
	std::memcpy(c.buffer, buffer, length);
	st_utf8_encode(c.buffer + length, ch, l);
	return c;
}