#ifndef _COLD_RESOURCE_FILE_HANDLE_H
#define _COLD_RESOURCE_FILE_HANDLE_H

namespace cold {

struct FileHandle {
	FileHandle(FileHandle&& f);
	FileHandle& operator=(FileHandle&& f);
	~FileHandle();
	void* get_handle() const { return handle; }
	static FileHandle load_file(const char* file);
	static FileHandle load_mem(const void* mem, unsigned int size);
	void invalidate() { handle = nullptr; }
private:
	explicit FileHandle(void* h) : handle(h) { }
	FileHandle(const FileHandle& f);
	FileHandle& operator=(const FileHandle& f);
	void* handle;
};

}

#endif