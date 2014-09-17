#ifndef _COLD_RESOURCE_RAW_TEXTURE_H
#define _COLD_RESOURCE_RAW_TEXTURE_H

namespace cold {

struct RawTexture {
public:
	RawTexture(void (*f)(unsigned char* c)) : free_fn(f) { }
	RawTexture(const RawTexture& r);
	RawTexture& operator=(const RawTexture& r);
	RawTexture(RawTexture&& r);
	RawTexture& operator=(RawTexture&& r);
	~RawTexture();
	unsigned char* pixel_at(unsigned int x, unsigned int y) {
		return data + (x + y * width) * channels;
	}

	unsigned char *data;
	int width, height;
	int channels;
private:
	void (*free_fn)(unsigned char* c);
};

}

#endif