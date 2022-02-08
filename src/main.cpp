#include <Arduino.h>
#include <vars.h>

void updateVoxels() {
    randomSeed(analogRead(0));
    ledState newState = animations[currentAnimation]->getState(keyFrame);

    // Copy Values to other Array
    for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++)
            for (int z = 0; z < zLen; z++)
                currentStateTest[x][y][z] = newState[x][y][z];
}

void loop() {
    for (int z = 0; z < zLen; z++) //Transistoren
    {
        // Displaying current Frame
        for (int y = 0; y < yLen; y++) //Latches
        {
            digitalWrite(latchCpPins[y], LOW);
            for (int x = 0; x < xLen; x++) //LEDs
            {
                digitalWrite(latchInputPins[x], currentStateTest[x][y][z]);
            }
            digitalWrite(latchCpPins[y], HIGH);
            digitalWrite(latchCpPins[y], LOW);
        }
        digitalWrite(transistorPins[z], HIGH);
        delay(msPerLayer);
        digitalWrite(transistorPins[z], LOW);
    }

    // Progressing through the Animation
    splitFrame++;
    if (splitFrame >= framesPerKeyFrame) {
        Serial.println(keyFrame);
        splitFrame = 0;
        keyFrame++;
        if (animations[currentAnimation]->done() == 1) {
            Serial.println("Switching to Animation " + String(currentAnimation));

            keyFrame = 0;
            currentAnimation++;

            if (currentAnimation >= animationCount) {
                currentAnimation = 0;
            }
        }

        updateVoxels();
    }
}

void setup() {
    Serial.begin(9600);

    //Set all Latch Input Pins to Low
    for (int latchInputPin: latchInputPins)
        digitalWrite(latchInputPin, LOW);

    //Set all Copy Pins to Low
    for (int latchCpPin: latchCpPins)
        digitalWrite(latchCpPin, LOW);

    //Set all Transistors to Low
    for (int transistorPin: transistorPins)
        digitalWrite(transistorPin, LOW);
}
