#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "Audio.h"

class AudioPlayer {
    struct Item {
        Audio audio;
        Item* next;
        Item* prev;
    };
    Item* first;
    Item* last;
    Item* cur;
    bool loop;
    bool end;
    int volume;
    size_t len;
public:
    AudioPlayer()
        : first(0), last(0)
        , cur(0), loop(0)
        , end(0), volume(64)
        , len(0)
    {}
    ~AudioPlayer();
    Audio& Get() { return cur->audio; }
    void Add(const char* path);
    void Play()   { cur->audio.Play(); }
    void Pause()  { cur->audio.Pause(); }
    void Resume() { cur->audio.Resume(); }
    void Stop()   { cur->audio.Stop(); }
    void Next();
    void Prev();
    void SetVolume(int a_volume);
    void Loop()   { loop = true; }
    void Unloop() { loop = false; }
    bool IsLoop() { return loop; }
    size_t Len()  { return len; }
private:
    AudioPlayer(const AudioPlayer&) {}
    void operator=(const AudioPlayer&) {}
    void Push(const char* path);
};

#endif
