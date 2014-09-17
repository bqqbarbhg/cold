#ifndef _COLD_AUDIO_AUDIO_H
#define _COLD_AUDIO_AUDIO_H

#include <cold/util/unique_ptr.h>
#include <SDL.h>

namespace cold { namespace audio {

struct AudioInstance {
	~AudioInstance();
};
extern UniquePtr<AudioInstance> audio_instance;

bool initialize();

} }

#endif