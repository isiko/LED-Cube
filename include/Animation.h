#ifndef ANIMATION
#define ANIMATION

class Animation {
public:
    explicit Animation(int maxI);

    virtual ledState getState(int kFrame) = 0;

    virtual bool done();

    virtual void reset();

protected:
    int iterations;
    int maxIterations;
    bool isDone = false;
};

Animation::Animation(int maxI) {
    maxIterations = maxI;
    iterations = 0;
}

void Animation::reset() {
    iterations = 0;
    isDone = false;
}

bool Animation::done() {
    if((iterations >= maxIterations && maxIterations > 0) || isDone) {
        reset();
        return true;
    }
    return false;
}

#endif