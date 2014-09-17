#ifndef _COLD_UTIL_BUFFERED_STREAM_H
#define _COLD_UTIL_BUFFERED_STREAM_H

#include <iostream>

class BufferedStream
{
public:
	BufferedStream(std::istream &s, unsigned int buf_len);
	~BufferedStream();
	void read()
	{
		_stream.read(_buffer, _buffer_length);
		_buffer_end = (_ptr = _buffer) + _stream.gcount();
		_eof = !_stream.good();
	}
	char get()
	{
		if (++_ptr == _buffer_end) {
			if (_eof)
				return 0;
			read();
			if (_eof && _buffer == _buffer_end)
				return 0;
		}
		return *_ptr;
	}
	char peek()
	{
		if (_eof && _ptr == _buffer_end)
			return 0;
		return *_ptr;
	}
private:
	unsigned int _buffer_length;
	char *_buffer, *_buffer_end, *_ptr;
	bool _eof;
	std::istream &_stream;
};

#endif