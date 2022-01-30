#include <Arduino.h>

#include <vars.h>

#include <Animation.h>
#include "test.h"
#include "directLines.h"
#include "flash.h"

// Animations
#define animationCount 2
Animation *animations[animationCount] = {new DirectLines(10, true), new Flash(4)};

bool getVoxel(int x, int y, int z)
{
  return currentStateTest[x][y][z];
}

void updateVoxels(){
  randomSeed(analogRead(0));
  ledState newState = animations[currentAnimation]->getState(keyFrame);

  // Copy Values to other Array
  for (int x = 0; x < xLen; x++)
    for (int y = 0; y < yLen; y++)
      for (int z = 0; z < zLen; z++)
        currentStateTest[x][y][z] = newState[x][y][z];
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
    if (animations[currentAnimation]->done() == 1)
    {
      Serial.println("Switching to Animation " + String(currentAnimation));

      animations[currentAnimation]->reset();
      keyFrame = 0;
      currentAnimation++;
      
      if (currentAnimation >= animationCount){
        currentAnimation = 0;
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
