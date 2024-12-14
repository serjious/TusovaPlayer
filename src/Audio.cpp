#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "Audio.h"

int init_audio()
{
	int init;
    init = SDL_Init(SDL_INIT_AUDIO);
    if(init == -1) {
		printf("Failure init: %s", Mix_GetError());
		return -1;
	}
    init = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                         MIX_DEFAULT_FORMAT,
                         MIX_DEFAULT_CHANNELS,
                         4096);
    if(init == -1) {
        printf("Failure init: %s", Mix_GetError());
        return -1;
	}
    return 0;
}

Audio::~Audio() {
	Mix_FreeMusic(ptr_mus);
}

void Audio::Load(const char* a_path)
{
    const char* a_name = a_path + strlen(a_path);
    for( ; a_name > a_path; a_name--) {
        if(*a_name == '\\' || *a_name == '/') {
            a_name++;
            break;
        }
    }
    ptr_mus = Mix_LoadMUS(a_path);
    if(!ptr_mus)
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
}

void Audio::Play()
{
	const int unloop = 1;
	int st = Mix_PlayMusic(ptr_mus, unloop);
    printf("%s\n", Title());
	if(st == -1)	
		printf("Mix_PlayMusic: path: %s (%s)\n", Mix_GetError());
}

void Audio::Pause() {
	Mix_PauseMusic();
}

void Audio::Resume() {
	Mix_ResumeMusic();
}

void Audio::Stop() {
	Mix_HaltMusic();
}

int Audio::SetVolume(int volume)
{
    // 0<=volume<=128
    // -1 return currect volume
    if(volume >= -1 && volume <= MIX_MAX_VOLUME)
		return Mix_VolumeMusic(volume);
    return 0;
}

void Audio::SetPosition(double pos) 
{
	int st = Mix_SetMusicPosition(pos);
	if(st == -1)
		printf("SetPosition: path: %s (%s)\n", Mix_GetError());
}

double Audio::GetPosition() {
	return Mix_GetMusicPosition(ptr_mus);
}

double Audio::Duration() {
	return Mix_MusicDuration(ptr_mus);
}

const char* Audio::Title() {
	return Mix_GetMusicTitle(ptr_mus);
}

const char* Audio::Artist() {
	return Mix_GetMusicArtistTag(ptr_mus);
}

const char* Audio::Album() {
	return Mix_GetMusicAlbumTag(ptr_mus);
}

const char* Audio::Copy() {
	return Mix_GetMusicCopyrightTag(ptr_mus);
}

bool Audio::Paused() {
	return Mix_PausedMusic();
}
