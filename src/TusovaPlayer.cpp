#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "OOFLButton.h"
#include "TusovaPlayer.h"
#include "AudioPlayer.h"

static const char* win_title = "TusovaPlayer";
static const char* play_msg = "Play";
static const char* prev_msg = "Prev";
static const char* next_msg = "Next";

extern AudioPlayer a_pl;

enum {
    spacing = 5,
    but_w = 30,
    but_h = 30,
    font_size = 10
};

class PlayButton : public OOFLButton {
public:
    PlayButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, play_msg)
        { labelsize(font_size); }
    virtual void OnPress() { a_pl.Get().Play(); }
};

class PrevButton : public OOFLButton {
public:
    PrevButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, prev_msg)
        { labelsize(font_size); }
    virtual void OnPress() { a_pl.Prev(); }
};

class NextButton : public OOFLButton {
public:
    NextButton(int x, int y)
        : OOFLButton(x, y, but_w, but_h, next_msg)
        { labelsize(font_size); }
    virtual void OnPress() { a_pl.Next(); }
};


int run(const char* path)
{
    a_pl.Loop();
    a_pl.Add(path);
    if(a_pl.Len() > 0)
        a_pl.Get().Play();
    Fl_Window* win = new Fl_Window(100, 100, 340, 120, win_title);
    new PlayButton(spacing, but_h * 2);
    new PrevButton(spacing * 2 + but_w, but_h * 2);
    new NextButton(spacing * 3 + but_w * 2, but_h * 2);
    win->end();
    win->show();
    return Fl::run();
}
