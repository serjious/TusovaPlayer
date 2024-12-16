#ifndef OOFLBUTTON_H
#define OOFLBUTTON_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>


class OOFLButton : public Fl_Button {
public:
    OOFLButton(int x, int y, int w, int h, const char *lb)
        : Fl_Button(x, y, w, h, lb)
        { callback(CallbackFunction, 0); }
    virtual ~OOFLButton() {}
    virtual void OnPress() {}
private:
    static void CallbackFunction(Fl_Widget *w, void *user)
        { static_cast<OOFLButton*>(w)->OnPress(); }
};

#endif
