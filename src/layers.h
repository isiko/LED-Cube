// Puts on all LEDs one by one

#include <Arduino.h>
#include "Animation.h"

class Layers : public Animation {
public:
    explicit Layers(bool pX, bool pY, bool pZ);

    ledState getState(int kFrame) override;

    void reset() override;

private:
    bool showAxies[3];

    int counters[3] = {0, 0, 0};
};

Layers::Layers(bool pX, bool pY, bool pZ) : Animation(4) {
    showAxies[0] = pX;
    showAxies[1] = pY;
    showAxies[2] = pZ;
}

ledState Layers::getState(int kFrame) {
    static bool state[xLen][yLen][zLen] = {0};

    for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++)
            for (int z = 0; z < zLen; z++)
                state[x][y][z] = (
                        (showAxies[0] && x == counters[0]) ||
                        (showAxies[1] && y == counters[1]) ||
                        (showAxies[2] && z == counters[2])
                );

    iterations++;

    for (int i = 0; i < 3; ++i)
        counters[i] += showAxies[i];

    return state;
}

void Layers::reset() {
    counters[0] = 0;
    counters[1] = 0;
    counters[2] = 0;
    iterations = 0;
}