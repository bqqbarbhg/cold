#ifndef _COLD_AUDIO_SOUND_MANAGER_H
#define _COLD_AUDIO_SOUND_MANAGER_H

#include <cold/audio/channel.h>

template <typename T> class SizedStack;
template <typename T> class UniqueArray;
namespace cold {
class Sound;
namespace audio {
class SoundManager {
public:
	static void set_channels(unsigned int count);
	static int get_channel(audio::Priority p);
	static void play_sound(int channel, const Sound& s, int loops);
private:
	static void initialize();
	static bool _initialized;
	static SizedStack<int> free_channels;
	static UniqueArray<Channel> channels;
};

} }

#endif