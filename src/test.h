// Puts on all LEDs one by one

#include <Arduino.h>
#include "Animation.h"

class Test : public Animation {
public:
    explicit Test();

    ledState getState(int kFrame) override;
};

Test::Test() : Animation(xLen * yLen * zLen) {

}

ledState Test::getState(int kFrame) {
    static bool state[xLen][yLen][zLen] = {0};

    for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++)
            for (int z = 0; z < zLen; z++)
                state[x][y][z] = (
                        x == (keyFrame % (xLen * yLen)) % xLen &&
                        y == (keyFrame % (xLen * yLen)) / yLen &&
                        z == keyFrame / (xLen * yLen)
                );

    iterations++;

    return state;
}