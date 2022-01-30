#include <Arduino.h>
#define xLen 4
#define yLen 4
#define zLen 4 //height

#define FPS 90
#define framesPerKeyFrame 45

#define animationCount 3

// Pins
const int latchInputPins[xLen]  = {9, 8, 7, 6};
const int latchCpPins[yLen]     = {2, 3, 4, 5};
const int transistorPins[zLen]  = {15, 14, 16, 10};

// Animations
const int animationFrameCounts[animationCount] = {4, 7, 15};

// Counters
int keyFrame  = 0;  // Current KeyFrame
int aFrame    = 0;  // Current Splitframe
int animation = 0;  // Current Animation

// Calculated Variables
int msPerFrame = 1000/FPS;
int msPerLayer = msPerFrame/zLen;

// LED State
bool ledState[xLen][yLen][zLen];

bool getVoxel(int x, int y, int z)
{
  return ledState[x][y][z];
}

void updateVoxels(){
  for (int x = 0; x < xLen; x++)
    for (int y = 0; y < yLen; y++)
      for (int z = 0; z < zLen; z++)
        switch (animation)
        {
          // Animation 0 - Blink all LEDs
          case 0:
            if(keyFrame == 0)
              ledState[x][y][z] = 0;
            else
              ledState[x][y][z] = !ledState[x][y][z];
            break;

          // Animation 1 - Random Pattern
          case 1:
            ledState[x][y][z] = rand() & 1;
            break;

          // Animation 2 - Go through each Vertical Line of LEDs
          case 2:
            ledState[x][y][z] = ((x == keyFrame % xLen && y == keyFrame / yLen));
            break;

          // Turn of all LED's as a default
          default:
            ledState[x][y][z] = 0;
            break;
        }
}

void loop()
{
  for (int z = 0; z < zLen; z++) //Transistoren
  {
    // Displaying current Frame
    for (int y = 0; y < yLen; y++) //Latches
    {
      digitalWrite(latchCpPins[y],LOW);
      for (int x = 0; x < xLen; x++) //LEDs
      {
        digitalWrite(latchInputPins[x], getVoxel(x,y,z));
      }
      digitalWrite(latchCpPins[y], HIGH);
      digitalWrite(latchCpPins[y], LOW);
    }
    digitalWrite(transistorPins[z], HIGH);
    delay(msPerLayer);
    digitalWrite(transistorPins[z], LOW);
  }

  // Progressing through the Animation
  aFrame++;
  if (aFrame >= framesPerKeyFrame)
  {
    Serial.println(keyFrame);
    aFrame = 0;
    keyFrame++;
    if (keyFrame > animationFrameCounts[animation])
    {
      Serial.println("Switching to Animation " + String(animation));
      keyFrame = 0;
      animation++;
      if (animation >= animationCount){
        animation = 0;
      }
    }

    updateVoxels();
  }
}

void setup()
{
  Serial.begin(9600);

  //Set all Latch Input Pins to Low
  for (int z = 0; z < zLen; z++)
    digitalWrite(latchInputPins[z], LOW);

  //Set all Copy Pins to Low
  for (int y = 0; y < yLen; y++)
    digitalWrite(latchCpPins[y], LOW);

  //Set all Transistors to Low
  for (int x = 0; x < xLen; x++)
    digitalWrite(transistorPins[x], LOW);
}
