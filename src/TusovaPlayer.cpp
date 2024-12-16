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
    VolumeRoller(int x, int y)
        : OOFLRoller(x, y, rol_w, rol_h, msg_arr[key_vol])
    {
        bounds(rol_min, rol_max);
        value(rol_value);
        step(rol_step);
        type(FL_HORIZONTAL);
        do_callback();
    }
    virtual void OnRoll() { a_pl.SetVolume((int)(value()*vol_max)); }
};
/*
void VolumeRoller::Settings(int x, int y)
{
    bounds(rol_min, rol_max);
    value(0.5);
    step(0.01);
    type(FL_HORIZONTAL);
}
*/
class PlayBar : public OOFLHor_Nice_Slider {
public:
    PlayBar(int x, int y)
        : OOFLHor_Nice_Slider(x, y, bar_w, bar_h)
        { bounds(rol_min, rol_max);
          value(0);
          step(rol_step);
        }
    virtual void OnPress()
        { a_pl.Get().SetPosition(value()*a_pl.Get().Duration()); }
    void update()
        { value(a_pl.Get().GetPosition()/a_pl.Get().Duration()); }
};

static void callback_set_bar(void* w) {
    static_cast<PlayBar*>(w)->update(); 
    Fl::repeat_timeout(0.01, callback_set_bar, w);
}

int run(const char* path)
{
    a_pl.Loop();
    a_pl.Add(path);
    if(a_pl.Len() > 0)
        a_pl.Get().Play();
    Fl_Window* win = new Fl_Window(pos_x, pos_y, win_w,
                                   win_h, msg_arr[key_title]);
    new PlayButton(spacing, but_h * 2);
    new PrevButton(spacing * 2 + but_w, but_h * 2);
    new NextButton(spacing * 3 + but_w * 2, but_h * 2);
    new LoopButton(spacing * 4 + but_w * 3, but_h * 2);
    new VolumeRoller(but_w * 5, but_h * 2);
    PlayBar *bar = new PlayBar((win_w-bar_w)/2, spacing * 2);
    win->end();
    win->show();
    Fl::add_timeout(0.01, callback_set_bar, bar);
    return Fl::run();
}
