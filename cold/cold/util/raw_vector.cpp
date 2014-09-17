#include "raw_vector.h"
#include <cstdlib>
#include <algorithm>

namespace cold {

RawVector::RawVector(unsigned int s)
	: _size(s)
{
	if (s)
		_data = (char*)malloc(s);
	else
		_data = NULL;
}
RawVector::RawVector(const RawVector& v)
	: _size(v._size)
{
	_data = (char*)malloc(_size);
	memcpy(_data, v._data, _size);
}
RawVector::~RawVector() {
	free(_data);
}
RawVector& RawVector::operator=(RawVector rhs) {
	std::swap(*this, rhs);
	return *this;
}

void RawVector::reserve(unsigned int l) {
	_data = (char*)realloc(_data, _size += l);
}

}