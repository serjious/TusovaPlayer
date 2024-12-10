#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


enum {
    name_len = 256,
    path_len = 4096
};

class Audio {
    char name[name_len];     
    char path[path_len];
    Mix_Music* ptr_mus;
public:
    Audio() : ptr_mus(0) {}
    Audio(const char* a_path) { Load(a_path); }
    ~Audio() { }
    void Load(const char* path);
    void Play() { Mix_PlayMusic(ptr_mus, 1); }
    void Pause() { Mix_PauseMusic(); }
    void Resume() { Mix_ResumeMusic(); }
    void Stop() { Mix_HaltMusic(); }
    void SetVolume(int volume);
    int GetVolume() { return Mix_GetMusicVolume(ptr_mus); }
    void SetPosition(double pos) { Mix_SetMusicPosition(pos); }
    double GetPosition() { return Mix_GetMusicPosition(ptr_mus); }
    double Duration() { return Mix_MusicDuration(ptr_mus); }
    const char* Title() { return Mix_GetMusicTitle(ptr_mus); }
    const char* Artist() { return Mix_GetMusicArtistTag(ptr_mus); }
    const char* Album() { return Mix_GetMusicAlbumTag(ptr_mus); }
    const char* Copy() { return Mix_GetMusicCopyrightTag(ptr_mus); }
    bool Paused() { return Mix_PausedMusic(); }
};

void Audio::Load(const char* a_path)
{
    const char* a_name = a_path + strlen(a_path);
    for( ; a_name > a_path; a_name--) {
        if(*a_name == '\\' || *a_name == '/') {
            a_name++;
            break;
        }
    }
    strcpy(path, a_path);
    strcpy(name, a_name);
    ptr_mus = Mix_LoadMUS(path);
    if(!ptr_mus)
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
}

void Audio::SetVolume(int volume)
{
    // 0<=volume<=128
    Mix_VolumeMusic(volume);
}

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
public:
    AudioPlayer()
        : first(0)
        , last(0)
        , cur(0)
        , loop(0)
        , end(0)
        , volume(64)
    {}
    ~AudioPlayer() {}
    Audio& Cur() { return cur->audio; }
    void Add(const char* path);
    void Next();
    void Prev();
    void Loop() { loop = true; }
    void Unloop() { loop = false; }
    void SetVolume(int a_volume);
    bool IsLoop() { return loop; }
private:
    AudioPlayer(const AudioPlayer&) {}
    void operator=(const AudioPlayer&) {}
};

void AudioPlayer::Add(const char* path)
{
    if(!first) {
        first = new Item;
        first->audio.Load(path);
        first->audio.SetVolume(volume);
        first->next = NULL;
        first->prev = NULL;
        last = first;
        cur = first;
    } else {
        Item* tmp = new Item;
        tmp->audio.Load(path);
        tmp->audio.SetVolume(volume);
        tmp->next = NULL;
        tmp->prev = NULL;
        last->next = tmp;
        tmp->prev = last;
        last = tmp;
    }
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
    Item* tmp = first;
    while(tmp->next) {
        tmp->audio.SetVolume(a_volume);
        tmp = tmp->next;
    }
}
void init_sdl()
{
    int init;
    init = SDL_Init(SDL_INIT_AUDIO);
    if(init == -1)
        exit(1);
    init = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                         MIX_DEFAULT_FORMAT,
                         MIX_DEFAULT_CHANNELS,
                         4096);
    if(init == -1)
        exit(1);

}
int main()
{
    init_sdl();
    AudioPlayer a_list;
    a_list.Loop();
    a_list.Add("eliz.mp3");
    a_list.Add("eliz2.mp3");
    a_list.Add("eliz3.mp3");

    int c;
    while((c = getchar()) != EOF) {
        switch(c) {
        case 'p':
            if(a_list.Cur().Paused())
                a_list.Cur().Resume();
            else 
                a_list.Cur().Pause();
            break;
        case 'n':
            a_list.Cur().Play();
            break;
        case 'i':
            a_list.Prev();
            a_list.Cur().Play();
            break;
        case 'o':
            a_list.Next();
            a_list.Cur().Play();
            break;
        case 'b':
            a_list.Cur().Stop();
            break;
        case 'l':
            if(a_list.IsLoop()) {
                printf("unloop");
                a_list.Unloop();
            } else {
                printf("unloop");
                a_list.Unloop();
            }
            break;
        case 'y':
            a_list.SetVolume(10);
            break;
        }
    }

    return 0;
}
/*
int main(int argc, char* argv[])
{
    int init;
    init = SDL_Init(SDL_INIT_AUDIO);
    if(init == -1)
        return 1;
    init = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                         MIX_DEFAULT_FORMAT,
                         MIX_DEFAULT_CHANNELS,
                         4096);
    if(init == -1)
        return 1;

    if(argc < 1)
        return 1;
    Audio a("eliz.mp3");
    a.SetVolume(1);
    a.Play();
    printf("%d\n", a.GetVolume());
    int c;
    while((c = getchar()) != EOF)
    {
        if(c == 'n')
            a.Play();
        if(c == 'p') {
            if(a.Paused())
                a.Resume();
            else 
                a.Pause();
        }
        if(c == 's')
            printf("position s %f\n", a.GetPosition()); 
        if(c == 'd')
            printf("duration s %f\n", a.Duration()); 
    }
    return 0;    
}
*/
