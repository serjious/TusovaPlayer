#ifndef DIR_SCAN_H
#define DIR_SCAN_H

#include "AudioPlayer.h"

bool is_music(const char* path);

bool is_directory(const char* path);

void dir_scan(const char* path, AudioPlayer& obj);

#endif
