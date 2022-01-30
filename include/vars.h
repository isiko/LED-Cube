#ifndef VARS
#define VARS

//Hardware Related Values
#define xLen 4
#define yLen 4
#define zLen 4 //height
const int latchInputPins[xLen] = {9, 8, 7, 6};
const int latchCpPins[yLen] = {2, 3, 4, 5};
const int transistorPins[zLen] = {15, 14, 16, 10};

//Framerate Related Values
#define FPS 90
#define framesPerKeyFrame 10
int msPerFrame = 1000 / FPS;
int msPerLayer = msPerFrame / zLen;

// Variables and Counters
int keyFrame = 0;  // Current KeyFrame
int aFrame = 0;    // Current Splitframe
int currentAnimation = 0; // Current Animation

// LED State
bool standard[xLen][yLen][zLen] = {0};
typedef bool (&ledState)[xLen][yLen][zLen];
ledState currentStateTest = standard;

#endif