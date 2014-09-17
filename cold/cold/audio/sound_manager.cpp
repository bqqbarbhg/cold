#include "sound_manager.h"
#include <cold/util/sized_stack.h>
#include <cold/util/unique_array.h>
#include <cold/audio/sound.h>
#include <SDL_mixer.h>
#include <cstring>
#include <utility>

static inline unsigned int min(unsigned int a, unsigned int b) {
	return a < b ? a : b;
}

namespace cold { namespace audio {

bool SoundManager::_initialized = false;
SizedStack<int> SoundManager::free_channels;
UniqueArray<Channel> SoundManager::channels;

void SoundManager::set_channels(unsigned int count) {
	count = Mix_AllocateChannels(count);
	if (!SoundManager::_initialized) {
		SoundManager::initialize();
		channels = UniqueArray<Channel>(count);
		free_channels = SizedStack<int>(count);
		for (int i = count - 1; i >= 0; --i) {
			free_channels.push(i);
		}
	} else {
		UniqueArray<Channel> n_channels(count);
		std::memcpy(n_channels.begin(), channels.end(), min(n_channels.size(), channels.size()));
		channels = std::move(n_channels);
		SizedStack<int> n_free(count);
		std::memcpy(n_free.begin(), free_channels.begin(), min(free_channels.count(), n_free.size()));
		for (int i = count - 1; i >= (int)free_channels.size(); --i) {
			n_free.push(i);
		}
		free_channels = std::move(n_free);
	}
}

int SoundManager::get_channel(audio::Priority p) {
	if (free_channels.empty()) {
		std::pair<int, Channel*> pair = std::pair<int, Channel*>(100, nullptr);
		for (Channel* c = channels.begin(); c != channels.end(); c++) {
			// TODO(bqq): Better priority handling
			int d = (int)c->priority - (int)p;
			if (d < pair.first)
				pair = std::make_pair(d, c);
		}
		if (pair.second == nullptr)
			return -1;
		Mix_HaltChannel(pair.second - channels.begin());
	}
	else
		return free_channels.pop();
	return 0;
}

void SoundManager::play_sound(int channel, const Sound& s, int loops) {
	Mix_PlayChannel(channel, (Mix_Chunk*)s.get_handle(), loops);
}

void SoundManager::initialize() {
	_initialized = true;
}

} }