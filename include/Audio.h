#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

class Audio {
    Mix_Music* ptr_mus;
public:
    Audio() : ptr_mus(0) {}
    Audio(const char* a_path) { Load(a_path); }
    ~Audio();
    void Load(const char* path);
    void Play();
    void Pause();
    void Resume();
    void Stop();
    int SetVolume(int volume);
    int GetVolume() { return SetVolume(-1); }
    void SetPosition(double pos);
    double GetPosition();
    double Duration();
    const char* Title();
    const char* Artist();
    const char* Album();
    const char* Copy();
    bool Paused();
};

int init_audio();
//static method mb

#endif
