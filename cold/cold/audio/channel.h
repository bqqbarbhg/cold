#ifndef _COLD_AUDIO_CHANNEL_H
#define _COLD_AUDIO_CHANNEL_H
#include <cold/audio/priority.h>

namespace cold { namespace audio {

struct Channel {
	unsigned int length;
	bool reserved;
	Priority priority;
};

} }

#endif