#include "file_handle.h"
#include <SDL_rwops.h>

namespace cold {

FileHandle::FileHandle(FileHandle&& f)
	: handle(f.handle)
{
	f.handle = nullptr;
}
FileHandle& FileHandle::operator=(FileHandle&& f) {
	if (f.handle == handle)
		return *this;
	handle = f.handle;
	f.handle = nullptr;
	return *this;
}
FileHandle FileHandle::load_file(const char* file) {
	return FileHandle(SDL_RWFromFile(file, "rb"));
}
FileHandle FileHandle::load_mem(const void* mem, unsigned int size) {
	return FileHandle(SDL_RWFromConstMem(mem, size));
}
FileHandle::~FileHandle() {
	if (handle != nullptr)
		SDL_FreeRW((SDL_RWops*)handle);
}

}