// Moves from Corner to Corner

#include <Arduino.h>
#include <Animation.h>

class DirectLines : public Animation
{
    public:
        virtual ledState getState(int keyFrame);
        virtual bool done();
        virtual void reset();

        DirectLines(int targetAmount, bool pShowTraces){
            targets = targetAmount;
            showTrace = pShowTraces;
            setRandomTarget();
        }

    private:
        void setRandomTarget();

        bool state[xLen][yLen][zLen];

        int current[3] = {0, 0, 0};
        int target[3];

        int targetCounter = 0;
        int targets;

        bool showTrace = true;

};

void DirectLines::setRandomTarget()
{
    bool oldTarget[3] = {target[0], target[1], target[2]};

    do
    {
        target[0] = (xLen - 1) * random(2);
        target[1] = (yLen - 1) * random(2);
        target[2] = (zLen - 1) * random(2);
    } while (
        oldTarget[0] == target[0] &&
        oldTarget[1] == target[1] &&
        oldTarget[2] == target[2]
    );
}

ledState DirectLines::getState(int keyFrame)
{
    for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++)
            for (int z = 0; z < zLen; z++)
                state[x][y][z] = (z == current[0] && y == current[1] && x == current[2]) || (state[x][y][z] && showTrace);

    if (
        current[0] == target[0] &&
        current[1] == target[1] &&
        current[2] == target[2])
    {
        setRandomTarget();
        targetCounter++;
    }
    

    for (int i = 0; i < 3; i++)
    {
        if (current[i] > target[i])
            current[i]--;

        if (current[i] < target[i])
            current[i]++;
    }

    return state;
}

bool DirectLines::done(){
    return targetCounter > targets;
}

void DirectLines::reset()
{
    memset(state, 0, sizeof(state));
    targetCounter = 0;
}