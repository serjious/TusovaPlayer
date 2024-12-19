#include <FL/Fl_PNG_Image.H>
#include "TusovaPlayer.h"
#include "Error.h"

static const char* title_img = "title.png";

void VolumeRoller::Logic()
{
        bounds(rol_min, rol_max);
        value(rol_value);
        step(rol_step);
        type(FL_HORIZONTAL);
        do_callback();
}

void PlayButton::OnPress()
{
    if(a_pl.Get().Paused()) {
        a_pl.Get().Resume();
        label(msg_arr[key_pause]);
    } else {
        a_pl.Get().Pause();
        label(msg_arr[key_play]);
    }
}

void LoopButton::OnPress()
{
    printf("%d\n", a_pl.IsLoop());
    if(a_pl.IsLoop()) {
        a_pl.Unloop();
        label(msg_arr[key_unloop]);
    } else {
        a_pl.Loop();
        label(msg_arr[key_loop]);
    }
}

void PlayBar::Logic()
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

void MainWindow::Logic(int argc, char* argv[])
{
    if(argc > 1)
        for(int i = 1; i < argc; i++)
            a_pl.Add(argv[i]);
    try {
        a_pl.Get().Play();
        can_upd = 1;
    }
    catch(const EmptyListError& a)
    {
        printf("%s\n", a.What());
        exit(1);
    }

    PlayButton* but = new PlayButton(spacing, but_h * 2);
    new PrevButton(spacing * 2 + but_w, but_h * 2);
    new NextButton(spacing * 3 + but_w * 2, but_h * 2);
    new LoopButton(spacing * 4 + but_w * 3, but_h * 2);
    new VolumeRoller(but_w * 5, but_h * 2);
    TimePosition *pos_t = new TimePosition(spacing, spacing * 2);
    TimeDuration *dur_t = new TimeDuration(win_w - time_w - spacing, spacing * 2);
    PlayBar *bar = new PlayBar((win_w - bar_w) / 2, spacing * 2);
    Fl_PNG_Image *img = new Fl_PNG_Image(title_img);
    end();
    icon(img);
    show();
    Fl::add_timeout(bar_timeout, PlayBar::UpdateCallback, bar);
    Fl::add_timeout(time_timeout, TimePosition::UpdateCallback, pos_t);
    Fl::add_timeout(time_timeout, TimeDuration::UpdateCallback, dur_t);
    Fl::add_timeout(win_timeout, MainWindow::UpdateCallback, this);
}

void MainWindow::UpdateCallback(void* w)
{
    MainWindow *win = static_cast<MainWindow*>(w);
    if(win->can_upd) {
        win->Update();
        Fl::repeat_timeout(win_timeout, UpdateCallback, w);
    }
}


