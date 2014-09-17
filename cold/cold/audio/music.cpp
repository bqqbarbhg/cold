#include "music.h"
#include <cold/resource/file_handle.h>
#include <cold/resource/resource.h>
#include <cold/resource/file_handle.h>
#include <cold/resource/load_info.h>
#include <cold/resource/resource_loader.h>
#include <SDL_mixer.h>
#include <utility>
#include <string>

namespace cold {

Music::Music(FileHandle&& fh)
{
	music_handle = Mix_LoadMUS_RW((SDL_RWops*)fh.get_handle());
	fh.invalidate();
}
Music::Music(Music&& m)
	: music_handle(m.music_handle)
{
	m.music_handle = nullptr;
}
Music& Music::operator=(Music&& m) {
	music_handle = m.music_handle;
	m.music_handle = nullptr;
	return *this;
}
Music::~Music() {
	if (music_handle != nullptr)
		Mix_FreeMusic((Mix_Music*)music_handle);
}
void Music::set_volume(float vol) {
	Mix_VolumeMusic(vol * MIX_MAX_VOLUME);
}
void Music::play(int loops)	{
	Mix_PlayMusic((Mix_Music*)music_handle, loops);
}
template <>
Resource<Music>* Resource<Music>::load(const ResourceLoadInfo& info) {
	std::string s;
	if (!info.get_arg("source", s)) return nullptr;
	// TODO(bqq): Add flags
	return new Resource<Music>(Music(ResourceLoader::get()->load_file(s)));
}

}