#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include "../include/dirent_win32.h"
#else
#include <dirent.h>
#endif
#include <dir_scan.h>

static const char* music_types[]{
    ".mp3",   ".MP3",
    ".wav",   ".WAV",
    ".ogg",   ".OGG",
    ".flac",  ".FLAC",
    ".opus",  ".OPUS"
};

bool is_music(const char* path)
{
    for( ; *path; path++) {
        if(*path== '.') {
            int size_types = sizeof(music_types)/sizeof(*music_types);
            for(int i = 0; i < size_types; i++) {
                if(strcmp(path, music_types[i]) == 0)
                    return true;
            }
        }
    }
    return false;
}

bool is_directory(const char* path)
{
    DIR* dp = opendir(path);
    closedir(dp);
    return dp;
}

static void rec_dir_scan(const char* dir_name, AudioPlayer& obj)
{
    dirent** namelist;
    dirent* entry;
    int n = scandir(dir_name, &namelist, NULL, alphasort);
    if(n == -1)
        //error handling
        return;
    for(int i = 0; i < n; i++) {
        char path[PATH_MAX];
        entry = namelist[i];
        if(entry->d_type & DT_DIR) {
            if(strcmp(entry->d_name, "..") != 0 &&
               strcmp(entry->d_name, ".") != 0) {
                snprintf(path, PATH_MAX, "%s/%s", dir_name, entry->d_name);
                rec_dir_scan(path, obj); 
            }
        } else {
            if(is_music(entry->d_name)) {
                snprintf(path, PATH_MAX, "%s/%s", dir_name, entry->d_name);
                obj.Add(path);
            }
        }
        free(namelist[i]);
    }
    free(namelist);
    //errors handler
}

void dir_scan(const char* path, AudioPlayer& obj)
{
    char upd_dir_name[PATH_MAX]; 
    strncpy(upd_dir_name, path, PATH_MAX);
    // /home/user/ <- delete last slash
    for(char* tmp = upd_dir_name; *tmp; tmp++) {
        if(*(tmp+1) == '\0' && *tmp == '/')
            *tmp = '\0';
    }
    rec_dir_scan(upd_dir_name, obj);
}


