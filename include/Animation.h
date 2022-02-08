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
};

Animation::Animation(int maxI) {
    maxIterations = maxI;
    iterations = 0;
}

void Animation::reset() {
    iterations = 0;
}

bool Animation::done() {
    return iterations >= maxIterations;
}

#endif