#include "AudioPlayer.h"
#include "dir_scan.h"

void dir_scan(const char* path, AudioPlayer& obj);

AudioPlayer a_pl;

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
	} else 
		Push(path);
}
    
void AudioPlayer::Next()
{
    if(Len() == 0)
        return; 
    if(cur->next)
        cur = cur->next;
    else if(loop)
        cur = first;
    else
        end = true;
    if(!end)
        cur->audio.Play();
}

void AudioPlayer::Prev()
{
    if(Len() == 0)
        return;
    if(cur->prev)
        cur = cur->prev;
    else if(loop)
        cur = first;
    else
        end = true;
    if(!end)
        cur->audio.Play();
}

void AudioPlayer::SetVolume(int a_volume)
{
    printf("Change volume: %d\n", a_volume);
    volume = a_volume;
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

