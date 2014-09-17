#include "raw_texture.h"
#include <cstring>

namespace cold {

namespace {
void free_fn_default(unsigned char* c) {
	delete [] c;
}
}

RawTexture::RawTexture(const RawTexture& r)
	: width(r.width), height(r.height), channels(r.channels),
	free_fn(free_fn_default), data(new unsigned char[r.width * r.height * r.channels])
{
	std::memcpy(data, r.data, r.width * r.height * r.channels);
}
RawTexture& RawTexture::operator=(const RawTexture& r) {
	if (r.data == data)
		return *this;
	if (data)
		free_fn(data);
	unsigned int size = (width = r.width) * (height = r.height) * (channels = r.channels);
	data = new unsigned char[size];
	std::memcpy(data, r.data, size);
	free_fn = free_fn_default;
	return *this;
}
RawTexture::RawTexture(RawTexture&& r)
	: data(r.data), width(r.width), height(r.height), channels(r.channels), free_fn(r.free_fn)
{
	r.data = nullptr;
}
RawTexture& RawTexture::operator=(RawTexture&& r) {
	width = r.width;
	height = r.height;
	free_fn = r.free_fn;
	channels = r.channels;
	if (data == r.data) return *this;
	data = r.data;
	r.data = nullptr;
	return *this;
}
RawTexture::~RawTexture() {
	if (data)
		free_fn(data);
}

}