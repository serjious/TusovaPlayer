#ifndef OOFLROLLER_H
#define OOFLROLLER_H

#include <FL/Fl.H>
#include <FL/Fl_Roller.H>

class OOFLRoller : public Fl_Roller {
public:
    OOFLRoller(int x, int y, int w, int h, const char* lb)
        : Fl_Roller(x, y, w, h, lb)
        { callback(CallbackFunction, 0); }
    virtual ~OOFLRoller() {}
    virtual void OnRoll() {}
private:
    static void CallbackFunction(Fl_Widget *w, void *user)
        { static_cast<OOFLRoller*>(w)->OnRoll(); }
};

#endif
