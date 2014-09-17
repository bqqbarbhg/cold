#include "buffered_stream.h"

BufferedStream::BufferedStream(std::istream &s, unsigned int buf_len)
	: _stream(s), _buffer_length(buf_len)
{
	_buffer = new char[buf_len];
	read();
}
BufferedStream::~BufferedStream()
{
	delete[] _buffer;
}
