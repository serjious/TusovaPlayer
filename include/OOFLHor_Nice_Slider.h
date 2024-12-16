#ifndef OOFLHOR_NICE_SLIDER
#define OOFLHOR_NICE_SLIDER

#include <FL/Fl.H>
#include <FL/Fl_Hor_Nice_Slider.H>

class OOFLHor_Nice_Slider : public Fl_Hor_Nice_Slider {
public:
    OOFLHor_Nice_Slider(int x, int y, int w, int h, const char *lb = 0)
        : Fl_Hor_Nice_Slider(x, y, w, h, lb)
        { callback(CallbackFunction, 0); }
    virtual ~OOFLHor_Nice_Slider() {}
    virtual void OnPress() {} 
private:
    static void CallbackFunction(Fl_Widget* w, void* user)
        { static_cast<OOFLHor_Nice_Slider*>(w)->OnPress(); }
}; 

#endif
