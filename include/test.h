// Puts on all LEDs one by one

#include <Arduino.h>
#include <Animation.h>

class Test : public Animation
{
public:
    virtual ledState getState(int kFrame);
    virtual bool done();
    virtual void reset();

    int frameCounter = 0;
};

ledState Test::getState(int keyFrame)
{
    static bool state[xLen][yLen][zLen] = {0};

    for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++)
            for (int z = 0; z < zLen; z++)
                state[x][y][z] = (
                    x == (keyFrame % (xLen * yLen)) % xLen &&
                    y == (keyFrame % (xLen * yLen)) / yLen &&
                    z == keyFrame / (xLen * yLen)
                );

    frameCounter++;

    return state;
}

bool Test::done(){
    return frameCounter >= xLen * yLen * zLen;
}

void Test::reset(){
    frameCounter = 0;
}