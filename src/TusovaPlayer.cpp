#include <FL/Fl_PNG_Image.H>
#include "TusovaPlayer.h"

static const char* title_img = "title.png";

VolumeRoller::VolumeRoller(int x, int y)
: OOFLRoller(x, y, rol_w, rol_h, msg_arr[key_vol])
{
        bounds(rol_min, rol_max);
        value(rol_value);
        step(rol_step);
        type(FL_HORIZONTAL);
        do_callback();
}

PlayBar::PlayBar(int x, int y)
: OOFLHor_Nice_Slider(x, y, bar_w, bar_h)
{
	bounds(rol_min, rol_max);
	value(0);
	step(rol_step);
}

void PlayBar::UpdateCallback(void* bar)
{
    double t = static_cast<PlayBar*>(bar)->Update();
    if(t == rol_max)
        a_pl.Next();
    Fl::repeat_timeout(bar_timeout, UpdateCallback, bar);
}

double PlayBar::Update()
{
    double t = a_pl.Get().GetPosition() / a_pl.Get().Duration();
    value(t);
    return t;
}

void Time::UpdateCallback(void* t)
{
    static_cast<Time*>(t)->Update();
    Fl::repeat_timeout(time_timeout, UpdateCallback, t);
}

void Time::Update()
{
    Set();
    SetTime();
    value(time);
}

void Time::SetTime()
{
    int min = ((int)r_time / 60) % 60;
    int sec = (int)r_time % 60;
    snprintf(time, time_size, "%02d:%02d", min, sec);
}

int run(const char* path)
{
    //a_pl.Loop();
    a_pl.Add(path);
    Fl_Window* win = new Fl_Window(pos_x, pos_y, win_w,
                                   win_h, msg_arr[key_title]);
    PlayButton* but = new PlayButton(spacing, but_h * 2);
    new PrevButton(spacing * 2 + but_w, but_h * 2);
    new NextButton(spacing * 3 + but_w * 2, but_h * 2);
    new LoopButton(spacing * 4 + but_w * 3, but_h * 2);
    new VolumeRoller(but_w * 5, but_h * 2);
    TimePosition *f_t = new TimePosition(spacing, spacing * 2);
    TimeDuration *l_t = new TimeDuration(win_w - time_w - spacing, spacing * 2);
    PlayBar *bar = new PlayBar((win_w - bar_w) / 2, spacing * 2);
    if(a_pl.Len() > 0)
        but->OnPress();
    Fl_PNG_Image *img = new Fl_PNG_Image(title_img);
    win->end();
    win->icon(img);
    win->show();
    Fl::add_timeout(bar_timeout, PlayBar::UpdateCallback, bar);
    Fl::add_timeout(time_timeout, TimePosition::UpdateCallback, f_t);
    Fl::add_timeout(time_timeout, TimeDuration::UpdateCallback, l_t);
    return Fl::run();
}
