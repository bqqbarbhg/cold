#ifndef _COLD_RENDER_BASE_BUFFER_H
#define _COLD_RENDER_BASE_BUFFER_H

namespace cold { namespace impl {

class BaseBuffer {
public:
	~BaseBuffer();
	void set_data(const void *data, unsigned int size);
	void apply() const;
protected:
	BaseBuffer();
	BaseBuffer (const BaseBuffer&);
	BaseBuffer (BaseBuffer&&);
	BaseBuffer(unsigned int target, unsigned int usage);
	void operator= (BaseBuffer &&b);
private:
	BaseBuffer& operator= (const BaseBuffer&);
	unsigned int _buffer, _usage, _target;
};

} }

#endif