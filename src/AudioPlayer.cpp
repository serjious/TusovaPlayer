#include <SDL2/SDL_mixer.h>
#include "AudioPlayer.h"
#include "dir_scan.h"

void dir_scan(const char* path, AudioPlayer& obj);
void global_set_volume(int volume); 

AudioPlayer::~AudioPlayer()
{
	while(last) {
	    Item* tmp = last;
		last = tmp->prev;
		delete tmp;
    }
    printf("deleted track's: %d\n", len);
}

void AudioPlayer::Add(const char* path)
{
    if(is_directory(path)) {
		dir_scan(path, *this);
	} else if(is_music(path)) {
		Push(path);
    } else
        throw "blya";
}
    
void AudioPlayer::Next()
{
    if(cur->next)
        cur = cur->next;
    else if(loop)
        cur = first;
    else
        end = true;
}

void AudioPlayer::Prev()
{
    if(cur->prev)
        cur = cur->prev;
    else if(loop)
        cur = first;
    else
        end = true;
}

void AudioPlayer::SetVolume(int a_volume)
{
    volume = a_volume;
    /*
    Item* tmp = cur;
    while(tmp->next) {
        tmp->audio.SetVolume(a_volume);
        tmp = tmp->next;
    }
    tmp = cur->prev;
    if(tmp)
        while(tmp->prev) {
            tmp->audio.SetVolume(a_volume);
            tmp = tmp->prev;
        }
    */
    global_set_volume(a_volume);
}

void AudioPlayer::Push(const char* path)
{
    Item* tmp = new Item;
    tmp->audio.Load(path);
    tmp->audio.SetVolume(volume);
    if(!first) {
        first = tmp;
        first->next = 0;
        first->prev = 0;
        last = first;
        cur = first;
    } else {
        last->next = tmp;
        tmp->prev = last;
        last = tmp;
        last->next = 0;
    }
    len++;
}
