#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

const char* music_types[]{
    ".mp3",   ".MP3",
    ".wav",   ".WAV",
    ".ogg",   ".OGG",
    ".flac",  ".FLAC",
    ".opus",  ".OPUS"
};

static bool is_music(const char* name)
{
    for( ; *name; name++) {
        if(*name == '.') {
            int size_types = sizeof(music_types)/sizeof(*music_types);
            for(int i = 0; i < size_types; i++) {
                if(strcmp(name, music_types[i]) == 0)
                    return true;
            }
        }
    }
    return false;
}

static void rec_dir_scan(const char* dir_name)
{
    dirent** namelist;
    dirent* entry;
    int n = scandir(dir_name, &namelist, NULL, alphasort);
    if(n == -1)
        //error handling
        return;
    for(int i = 0; i < n; i++) {
        entry = namelist[i];
        if(entry->d_type & DT_DIR) {
            if(strcmp(entry->d_name, "..") != 0 &&
               strcmp(entry->d_name, ".") != 0) {
                char path[PATH_MAX];
                snprintf(path, PATH_MAX, "%s/%s", dir_name, entry->d_name);
                rec_dir_scan(path); 
            }
        } else {
            if(is_music(entry->d_name))
                printf("%s/%s\n", dir_name, entry->d_name);
        }
        free(namelist[i]);
    }
    free(namelist);
    //errors handler
}

void dir_scan(const char* dir_name)
{
    char upd_dir_name[PATH_MAX]; 
    strncpy(upd_dir_name, dir_name, PATH_MAX);
    // /home/user/ <- delete last slash
    for(char* tmp = upd_dir_name; *tmp; tmp++) {
        if(*(tmp+1) == '\0' && *tmp == '/')
            *tmp = '\0';
    }
    rec_dir_scan(upd_dir_name);
}

int main(int argc, char* argv[])
{
    if(argc < 1)
        return 1;
    //order_dir_scan(argv[1]);
    dir_scan(argv[1]);
    return 0;
}
