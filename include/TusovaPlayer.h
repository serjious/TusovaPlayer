#ifndef TUSOVAPLAYER_H
#define TUSOVAPLAYER_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "OOFLButton.h"
#include "OOFLRoller.h"
#include "OOFLHor_Nice_Slider.h"
#include "TusovaPlayer.h"
#include "AudioPlayer.h"

enum msg_key {
    key_title,
    key_play,
    key_prev,
    key_next,
    key_loop,
    key_vol
};

static const char* msg_arr[] = {
    "TusovaPlayer",
    "Play",
    "Prev",
    "Next",
    "Loop",
    "Volume"
};

extern AudioPlayer a_pl;

enum {
    pos_x = 0,
    pos_y = 0,
    win_w = 340,
    win_h = 120
};

enum {
    spacing = 5,
    but_w = 30,
    but_h = 30,
    font_size = 10
};

enum {
    rol_w = 100,
    rol_h = 25,
    rol_min = 0,
    rol_max = 1, 
    vol_max = 128
};

enum {
    bar_w = 240,
    bar_h = 20 
};

const static double rol_step = 0.01;
const static double rol_value = 0.01;
const static double play_bar_timeout = 0.01;

class PlayButton : public OOFLButton {
public:
    PlayButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, msg_arr[key_play])
        { labelsize(font_size); }
    virtual void OnPress() { a_pl.Get().Play(); }
};

class PrevButton : public OOFLButton {
public:
    PrevButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, msg_arr[key_prev])
        { labelsize(font_size); }
    virtual void OnPress() { a_pl.Prev(); }
};

class NextButton : public OOFLButton {
public:
    NextButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, msg_arr[key_next])
        { labelsize(font_size); }
    virtual void OnPress() { a_pl.Next(); }
};

class LoopButton : public OOFLButton {
public:
    LoopButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, msg_arr[key_loop])
        { labelsize(font_size); }
    virtual void OnPress() { a_pl.Loop(); }
};

class VolumeRoller : public OOFLRoller {
public:
    VolumeRoller(int x, int y);
    virtual void OnRoll() { a_pl.SetVolume((int)(value()*vol_max)); }
};

class PlayBar : public OOFLHor_Nice_Slider {
public:
    PlayBar(int x, int y);
    virtual void OnPress()
        { a_pl.Get().SetPosition(value()*a_pl.Get().Duration()); }
    static void UpdateCallback(void* bar);
private:
    void update()
        { value(a_pl.Get().GetPosition()/a_pl.Get().Duration()); }
};

int run(const char* path);

#endif
