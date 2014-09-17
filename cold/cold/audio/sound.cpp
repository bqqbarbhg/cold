#include "sound.h"
#include <cold/resource/resource.h>
#include <cold/resource/file_handle.h>
#include <cold/resource/load_info.h>
#include <cold/resource/resource_loader.h>
#include <cold/audio/sound_manager.h>
#include <SDL_mixer.h>

namespace cold {

Sound::Sound(FileHandle&& f) {
	handle = Mix_LoadWAV_RW((SDL_RWops*)f.get_handle(), 1);
	f.invalidate();
}
Sound::Sound(Sound&& s)
	: handle(s.handle)
{
	s.handle = nullptr;
}
Sound& Sound::operator=(Sound&& s) {
	handle = s.handle;
	s.handle = nullptr;
	return *this;
}
Sound::~Sound() {
	if (handle != nullptr)
		Mix_FreeChunk((Mix_Chunk*)handle);
}

void Sound::play(audio::Priority p, int loops) {
	int c = audio::SoundManager::get_channel(p);
	audio::SoundManager::play_sound(c, *this, loops);
}

template <>
Resource<Sound>* Resource<Sound>::load(const ResourceLoadInfo& info) {
	std::string s;
	if (!info.get_arg("source", s)) return nullptr;
	// TODO(bqq): Add flags
	return new Resource<Sound>(Sound(ResourceLoader::get()->load_file(s)));
}

}