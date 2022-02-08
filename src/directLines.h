// Moves from Corner to Corner

#include <Arduino.h>
#include <Animation.h>

class DirectLines : public Animation {
public:
    DirectLines(int targetAmount, int lifeSpan);

    ledState getState(int kFrame) override;

    void reset() override;

private:
    void setRandomTarget();

    bool state[xLen][yLen][zLen];
    int lifeTime[xLen][yLen][zLen] = {{{0}}};

    int current[3] = {0, 0, 0};
    int target[3];

    int defaultLifeSpan;

};

DirectLines::DirectLines(int targetAmount, int lifeSpan) : Animation(targetAmount) {
    defaultLifeSpan = lifeSpan;
    setRandomTarget();
}

void DirectLines::setRandomTarget() {
    int oldTarget[3] = {target[0], target[1], target[2]};

    do {
        target[0] = (xLen - 1) * random(2);
        target[1] = (yLen - 1) * random(2);
        target[2] = (zLen - 1) * random(2);
    } while (oldTarget[0] == target[0] && oldTarget[1] == target[1] && oldTarget[2] == target[2]);
}

ledState DirectLines::getState(int kFrame) {

    for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++)
            for (int z = 0; z < zLen; z++) {
                lifeTime[x][y][z]--;
                if(x == current[0] && y == current[1] && z == current[2])
                    lifeTime[x][y][z] = defaultLifeSpan;
                state[x][y][z] = lifeTime[x][y][z] > 0;
            }

    if (current[0] == target[0] && current[1] == target[1] && current[2] == target[2]) {
        Serial.println("Found Target (" + String(target[0]) + "|" + String(target[1]) + "|" + String(target[2]) + "|" + ")");
        setRandomTarget();
        iterations++;
    }

    for (int i = 0; i < 3; i++) {
        if (current[i] > target[i])
            current[i]--;

        if (current[i] < target[i])
            current[i]++;
    }

    return state;
}

void DirectLines::reset() {
    iterations = 0;
    memset(state, 0, sizeof(state));
    memset(lifeTime, 0, sizeof(lifeTime));

    // Set random Target and set the current pointer there to get a random Corner
    setRandomTarget();
    current[0] = target[0];
    current[1] = target[1];
    current[2] = target[2];

    // Set a new Target
    setRandomTarget();

}