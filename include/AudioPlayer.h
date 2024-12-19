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
    size_t len;
public:
    AudioPlayer()
        : first(0), last(0), cur(0)
        , loop(0), end(1), len(0) {}
    ~AudioPlayer();
    Audio& Get();
    void Add(const char* path);
    void Next();
    void Prev();
    void SetVolume(int a_volume);
    void Loop()   { loop = true; }
    void Unloop() { loop = false; }
    bool IsLoop() { return loop; }
    bool End()    { return end; }
    size_t Len()  { return len; }
private:
    AudioPlayer(const AudioPlayer&) {}
    void operator=(const AudioPlayer&) {}
    void Push(const char* path);
};

#endif
