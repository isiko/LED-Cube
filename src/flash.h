// Flashes all LEDs at once

#include <Arduino.h>
#include <Animation.h>

class Flash : public Animation {
public:
    explicit Flash(int maxI);

    ledState getState(int kFrame) override;

    void reset() override;

protected:
    bool isOn;
};

Flash::Flash(int maxI) : Animation(maxI) {
    isOn = false;
}

ledState Flash::getState(int kFrame) {
    isOn = !isOn;

    static bool state[xLen][yLen][zLen] = {false};
    for (auto &x: state)
        for (auto &y: x)
            for (bool &z: y)
                z = isOn;

    if (!isOn) {
        iterations++;
    }

    return state;
}

void Flash::reset() {
    iterations = 0;
}
