// Flashes all LEDs at once

#include <Arduino.h>
#include <Animation.h>

class Flash : public Animation
{
    public:
        int iterations = 0;
        int maxIterations;
        bool isOn = false;

        virtual ledState getState(int keyFrame);
        virtual bool done();
        virtual void reset();

        Flash(int flashAmount)
        {
            maxIterations = flashAmount;
        }
};

ledState Flash::getState(int keyFrame)
{
    isOn = !isOn;

    static bool state[xLen][yLen][zLen] = {0};
    for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++)
            for (int z = 0; z < zLen; z++)
                state[x][y][z] = isOn;

    if (!isOn)
    {
        iterations++;
    }
    

    return state;
}

bool Flash::done()
{
    return iterations >= maxIterations;
}

void Flash::reset()
{
    iterations = 0;
}