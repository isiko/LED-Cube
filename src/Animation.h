#ifndef ANIMATION
#define ANIMATION

#include <vars.h>

class Animation
{
    public:
        virtual ledState getState(int kFrame);
        virtual bool done();
        virtual void reset();
};

#endif