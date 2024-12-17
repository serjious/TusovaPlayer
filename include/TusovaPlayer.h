#ifndef TUSOVAPLAYER_H
#define TUSOVAPLAYER_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Output.H>
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
    bar_w = 220,
    bar_h = 20 
};

enum {
    time_w = 45,
    time_h = 20,
    time_size = 6
};

const static double rol_step = 0.01;
const static double rol_value = 0.5;
const static double bar_timeout = 0.01;
const static double time_timeout = 0.1;


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
    double Update();
};

class Time : public Fl_Output {
    // "00:00\0"
    char time[time_size];
public:
    double r_time;
    Time(int x, int y)
        : Fl_Output(x, y, time_w, time_h)
        , time("00:00"), r_time(0.0)
        { value(time); }
    ~Time() {}
    static void UpdateCallback(void* t);
    virtual void Set() { printf("hell\n"); }
private:
    void Update();
    void SetTime();
};

class TimePosition : public Time {
public:
    TimePosition(int x, int y)
        : Time(x, y) {}
    virtual Set() { r_time = a_pl.Get().GetPosition(); }
};


int run(const char* path);

#endif
