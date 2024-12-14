#include "AudioPlayer.h"
#include "dir_scan.h"


int main(int argc, char* argv[])
{
    if(argc < 1)
        return 1;

    if(init_audio() == -1)
        return 2;

    AudioPlayer a_pl;
    for(int i = 1; i < argc; i++) {
        if(argv[i] && (is_music(argv[i]) || is_directory(argv[i])))
            a_pl.Add(argv[i]);
    }
    
    if(a_pl.Len() == 0)
        return 3;
    
    
    int c;
    while((c = getchar()) != EOF) {
        switch(c) {
        case 'p':
            if(a_pl.Get().Paused())
                a_pl.Get().Resume();
            else 
                a_pl.Get().Pause();
            break;
        case 'n':
            a_pl.Get().Play();
            break;
        case 'i':
            a_pl.Prev();
            a_pl.Get().Play();
            break;
        case 'o':
            a_pl.Next();
            a_pl.Get().Play();
            break;
        case 'b':
            a_pl.Get().Stop();
            break;
        case 'l':
            if(a_pl.IsLoop()) {
                printf("unloop");
                a_pl.Unloop();
            } else {
                printf("unloop");
                a_pl.Unloop();
            }
            break;
        case 'y':
            a_pl.SetVolume(10);
            break;
        case 'u':
            a_pl.SetVolume(64);
            break;
        case 'q':
            return 0;
        }
    }

     
    return 0;
}
