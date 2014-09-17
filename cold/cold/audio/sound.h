#ifndef _COLD_AUDIO_SOUND_H
#define _COLD_AUDIO_SOUND_H
#include <cold/audio/priority.h>

namespace cold {
struct FileHandle;
class Sound {
public:
	Sound(FileHandle&& f);
	Sound(Sound&& s);
	Sound& operator=(Sound&& s);
	~Sound();
	void play(audio::Priority p, int loops=0);
	void* get_handle() const { return handle; }
private:
	void* handle;
};

}

#endif