#ifndef OOFLTIME_H
#define OOFLTIME_H

#include <FL/Fl.H>
#include <FL/Fl_Output.H>

enum {
    time_size = 9
};

const double time_timeout = 0.1;

class OOFLTime : public Fl_Output {
    // "00:00\0"
    double r_time;
    char time[time_size];
public:
    OOFLTime(int x, int y, int w, int h)
        : Fl_Output(x, y, w, h)
        , time("00:00:00"), r_time(0.0)
        { value(time); }
    ~OOFLTime() {}
    void RTime(double time) { r_time = time; }
    static void UpdateCallback(void* t);
    virtual void Set() {}
private:
    void Update();
};

#endif


