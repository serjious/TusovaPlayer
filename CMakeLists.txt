cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME tusovaplayer)
project(${PROJECT_NAME} LANGUAGES CXX)
message("Using ${CMAKE_CXX_COMPILER_ID} compiler")

set(HEADERS
            include/Audio.h
            include/AudioPlayer.h
            include/dir_scan.h
            include/dirent_win32.h)

set(SOURCES 
            src/main.cpp
            src/Audio.cpp
            src/AudioPlayer.cpp
            src/dir_scan.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(MINGW)
	target_link_libraries(${PROJECT_NAME} mingw32)
endif(MINGW)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_mixer)
