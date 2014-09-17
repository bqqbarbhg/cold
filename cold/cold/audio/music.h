#ifndef _COLD_AUDIO_MUSIC_H
#define _COLD_AUDIO_MUSIC_H

namespace cold {
struct FileHandle;
class Music {
public:
	Music(FileHandle&& fh);
	Music(Music&& m);
	Music& operator=(Music&& m);
	~Music();

	static void set_volume(float vol);
	void play(int loops=-1);
private:
	Music(const Music& m);
	Music& operator=(const Music& m);
	void *music_handle;
};

}

#endif