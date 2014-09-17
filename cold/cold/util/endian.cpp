#include "endian.h"

#include <cstdint>
#include <cstring>

namespace endian {

static const union {
	std::uint32_t u;
	char c[4];
} uu = { 0x0A0B0C0D };

const endianness value = (endianness)uu.c[0];

void _ch_flip_cpy(char* dest, const char* src, unsigned int len) {
	src += len;
	while (len--)
		*dest++ = *--src;
}

void _ch_memcpy(char* dest, const char* src, unsigned int len) {
	if (endian::value == BIG) {
		std::memcpy(dest, src, len);
	} else {
		flip_cpy(dest, src, len);
	}
}

};