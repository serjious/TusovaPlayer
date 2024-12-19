#ifndef TUSOVAPLAYER_H
#define TUSOVAPLAYER_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "OOFLTime.h"
#include "OOFLButton.h"
#include "OOFLRoller.h"
#include "OOFLHor_Nice_Slider.h"
#include "TusovaPlayer.h"
#include "AudioPlayer.h"

enum msg_key {
    key_title,
    key_play,
    key_pause,
    key_prev,
    key_next,
    key_loop,
    key_unloop,
    key_vol
};

static const char* msg_arr[] = {
    "TusovaPlayer",
    "Play",
    "Pause",
    "Prev",
    "Next",
    "Loop",
    "Unloop",
    "Volume"
};

extern AudioPlayer a_pl;

enum {
    pos_x = 2600,
    pos_y = 430,
    win_w = 380,
    win_h = 120
};

enum {
    spacing = 5,
    but_w = 35,
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
    time_w = 62,
    time_h = 20,
};

const static double rol_step = 0.01;
const static double rol_value = 0.5;
const static double bar_timeout = 0.01;
const static double win_timeout = 0.25;



class MainWindow : public Fl_Window{
    bool can_upd;
public:
    MainWindow(int argc, char* argv[])
        : Fl_Window(pos_x, pos_y, win_w, win_h, msg_arr[key_title])
        , can_upd(0)
        { Logic(argc, argv); }
    int Run() { return Fl::run(); }
    static void UpdateCallback(void* w);
private:
    void Logic(int argc, char* argv[]);
    void Update() { label(a_pl.Get().Title()); }
};

class PlayButton : public OOFLButton {
public:
    PlayButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, msg_arr[key_pause])
        { labelsize(font_size); }
    virtual void OnPress();
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
    virtual void OnPress();
};

class VolumeRoller : public OOFLRoller {
public:
    VolumeRoller(int x, int y)
        : OOFLRoller(x, y, rol_w, rol_h, msg_arr[key_vol])
        { Logic(); }
    virtual void OnRoll() { a_pl.SetVolume((int)(value()*vol_max)); }
private:
    void Logic();
};

class PlayBar : public OOFLHor_Nice_Slider {
public:
    PlayBar(int x, int y)
        : OOFLHor_Nice_Slider(x, y, bar_w, bar_h)
        { Logic(); }
    virtual void OnPress()
        { a_pl.Get().SetPosition(value()*a_pl.Get().Duration()); }
    static void UpdateCallback(void* bar);
private:
    double Update();
    void Logic();
};


class TimePosition : public OOFLTime {
public:
    TimePosition(int x, int y)
        : OOFLTime(x, y, time_w, time_h) {}
    virtual void Set() { RTime(a_pl.Get().GetPosition()); }
};

class TimeDuration : public OOFLTime {
public:
    TimeDuration(int x, int y)
        : OOFLTime(x, y, time_w, time_h) {}
    virtual void Set() { RTime(a_pl.Get().Duration()); }
};

#endif
