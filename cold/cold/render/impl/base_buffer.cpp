#include "base_buffer.h"
#include <cold/render/impl/gl.h>
#include <cold/util/assert.h>

namespace cold { namespace impl {

BaseBuffer::BaseBuffer()
{
	_buffer = 0;
}

BaseBuffer::BaseBuffer(unsigned int target, unsigned int usage)
	: _usage(usage), _target(target)
{
	glGenBuffers(1, &_buffer);
}

BaseBuffer::BaseBuffer(const BaseBuffer& b)
	: _buffer(0)
	, _target(0)
	, _usage(0)
{
	COLD_DEBUG_ASSERT(b._buffer == 0 && b._target == 0 && b._usage == 0);
}

BaseBuffer::BaseBuffer(BaseBuffer&& b)
	: _buffer(b._buffer)
	, _target(b._target)
	, _usage(b._usage)
{
	b._buffer = 0;
}

BaseBuffer::~BaseBuffer() {
	if (_buffer)
		glDeleteBuffers(1, &_buffer);
}

void BaseBuffer::operator= (BaseBuffer &&b) {
	if (_buffer)
		glDeleteBuffers(1, &_buffer);
	_buffer = b._buffer;
	_usage = b._usage;
	_target = b._target;
	b._buffer = 0;
}

void BaseBuffer::set_data(const void *data, unsigned int size) {
	COLD_DEBUG_ASSERT(_buffer != 0);
	apply();
	glBufferData(_target, size, data, _usage);
}

void BaseBuffer::apply() const {
	COLD_DEBUG_ASSERT(_buffer != 0);
	glBindBuffer(_target, _buffer);
}

} }