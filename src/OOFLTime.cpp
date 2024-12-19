#include <FL/Fl.H>
#include "OOFLTime.h"

void OOFLTime::UpdateCallback(void* t)
{
    static_cast<OOFLTime*>(t)->Update();
    Fl::repeat_timeout(time_timeout, UpdateCallback, t);
}

void OOFLTime::Update()
{
    Set();
    int itime = (int)r_time;
    int hour = (itime / (60 * 60)) % 60;
    int min = (itime / 60) % 60;
    int sec = itime % 60;
    snprintf(time, time_size, "%02d:%02d:%02d", hour, min, sec);
    value(time);
}
