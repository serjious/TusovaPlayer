#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

enum {
    name_size = 256
};

class Audio {
    char name[name_size];
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
    void SetPosition(double pos);
    double GetPosition() { return Mix_GetMusicPosition(ptr_mus); }
    double Duration() { return Mix_MusicDuration(ptr_mus); }
    const char* Title() { return name; }
    const char* Artist() { return Mix_GetMusicArtistTag(ptr_mus); }
    const char* Album() { return Mix_GetMusicAlbumTag(ptr_mus); }
    const char* Copy() { return Mix_GetMusicCopyrightTag(ptr_mus); }
    bool Paused() { return Mix_PausedMusic(); }
    static int InitAudio();
};

#endif
