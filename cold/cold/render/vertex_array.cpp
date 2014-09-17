#include "vertex_array.h"
#include <algorithm>
#include <cstdio>
#include <cold/render/impl/gl.h>

namespace cold {

VertexArray::VertexArray(const VertexDeclaration& vd, unsigned int s)
	: _vd(vd), _size(s)
{
	_data = (char*)malloc(_size * vd.stride);
}
VertexArray::VertexArray(const VertexArray& va)
	: _vd(va._vd), _size(va._size)
{
	_data = (char*)malloc(_size * _vd.stride);
	memcpy(_data, va._data, _size * _vd.stride);
}
VertexArray::~VertexArray() {
	free(_data);
}
VertexArray& VertexArray::operator=(VertexArray va) {
	std::swap(*this, va);
	return *this;
}
void VertexArray::apply() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	_vd.apply(_data);
}

}