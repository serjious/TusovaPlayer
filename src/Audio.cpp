#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "Audio.h"

int Audio::InitAudio()
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
    const char* title = Mix_GetMusicTitle(ptr_mus);
    if(*title) {
        strcpy(name, title);
    } else {
        const char* a_name = a_path + strlen(a_path);
        for( ; a_name > a_path; a_name--) {
            if(*a_name == '\\' || *a_name == '/') {
                a_name++;
                break;
            }
        }
        strcpy(name, a_name);
        for(int i = name_size - 1; i >= 0; i--)
            if(name[i] == '.')
                name[i] = '\0';
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


void Audio::SetPosition(double pos)
{
	int st = Mix_SetMusicPosition(pos);
	if(st == -1)
		printf("SetPosition: path: %s (%s)\n", Mix_GetError());
}
