#include "audio.h"
#include <SDL_mixer.h>

namespace cold { namespace audio {

UniquePtr<AudioInstance> audio_instance;

AudioInstance::~AudioInstance() {
	Mix_CloseAudio();
	Mix_Quit();
}

bool initialize() {
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 2048;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
		return false;
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != MIX_INIT_MP3 | MIX_INIT_OGG) {
		return false;
		Mix_CloseAudio();
	}
	audio_instance = new AudioInstance;
	return true;
}

} }