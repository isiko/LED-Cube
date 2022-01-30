#ifndef VARS
#define VARS

#define xLen 4
#define yLen 4
#define zLen 4 //height

#define FPS 90
#define framesPerKeyFrame 45

// Pins
const int latchInputPins[xLen] = {9, 8, 7, 6};
const int latchCpPins[yLen] = {2, 3, 4, 5};
const int transistorPins[zLen] = {15, 14, 16, 10};

typedef bool (&ledState)[xLen][yLen][zLen];

// Variables and Counters
int keyFrame = 0;  // Current KeyFrame
int aFrame = 0;    // Current Splitframe
int animation = 0; // Current Animation

#endif