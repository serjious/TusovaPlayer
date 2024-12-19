#include "AudioPlayer.h"
#include "dir_scan.h"
#include "Error.h"

AudioPlayer a_pl;

AudioPlayer::~AudioPlayer()
{
	while(last) {
	    Item* tmp = last;
		last = tmp->prev;
		delete tmp;
    }
    //printf("deleted track's: %d\n", len);
}

Audio& AudioPlayer::Get()
{
    if(!cur)
        throw EmptyListError();
    return cur->audio;
}

void AudioPlayer::Add(const char* path)
{
    if(is_directory(path)) {
		dir_scan(path, *this);
	} else
		Push(path);
}

void AudioPlayer::Next()
{
    if(!cur)
        throw EmptyListError();
    if(cur->next) {
        cur = cur->next;
        cur->audio.Play();
    }
    else if(loop) {
        cur = first;
        cur->audio.Play();
    }
    else
        end = true;
    if(!end)
        cur->audio.Play();
}

void AudioPlayer::Prev()
{
    if(!cur)
        throw EmptyListError();
    if(cur->prev) {
        cur = cur->prev;
        cur->audio.Play();
    }
    else if(loop) {
        cur = first;
        cur->audio.Play();
    }
    else
        end = true;
    if(!end)
        cur->audio.Play();
}

void AudioPlayer::SetVolume(int a_volume)
{
    Mix_VolumeMusic(a_volume);
}

void AudioPlayer::Push(const char* path)
{
    Item* tmp = new Item;
    tmp->audio.Load(path);
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

