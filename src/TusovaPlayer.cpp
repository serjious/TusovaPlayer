#include "TusovaPlayer.h"

struct title_win{
    Fl_Window* w;
    char* title;
};

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
    static_cast<PlayBar*>(bar)->update();
    Fl::repeat_timeout(play_bar_timeout, UpdateCallback, bar);
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
    PlayBar *bar = new PlayBar((win_w-bar_w)/2, spacing * 2);
    if(a_pl.Len() > 0)
        but->OnPress();
    win->end();
    win->show();
    Fl::add_timeout(play_bar_timeout, PlayBar::UpdateCallback, bar);
    return Fl::run();
}
