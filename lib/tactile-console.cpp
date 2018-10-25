#include "Arduino.h"
#include "tactile-console.h"

#define NORTH 6
#define SOUTH 9
#define EAST 10
#define WEST 11

#define ROT_A 2
#define ROT_B 4
#define STEPS 20
#define DEGREES_PER_CLICK 360 / STEPS

TactileConsole::TactileConsole() 
{
  pinMode(ROT_A, INPUT);
  pinMode(ROT_B, INPUT);
  a_val = digitalRead(ROT_A);
  b_val = digitalRead(ROT_B);
  angle = 0;
}

/**
 * Set the vibration inside the box
 * @param {float} angle The angle to vibrate, in degrees
 * @param {float} amplitude The amount to vibrate, between 0 and 1
 */
void TactileConsole::setVibration(float angle, float amplitude)
{
  float rads = d2r(angle + 90);
  float a = clamp(amplitude, 0, 1);
  float x = a * cos(rads);
  float y = a * sin(rads);

  analogWrite(EAST, (int)(x > 0 ? x * 255 : 0));
  analogWrite(WEST, (int)(x < 0 ? x * -255 : 0));
  analogWrite(NORTH, (int)(y > 0 ? y * 255: 0));
  analogWrite(SOUTH, (int)(y < 0 ? y * -255 : 0));
}

/**
 * Updates the internal rotation tracker. This needs to be called
 * inside the main loop at high frequency.
 */
void TactileConsole::listenForRotation()
{
  int a = digitalRead(ROT_A);
  int b = digitalRead(ROT_B);

  if (a == HIGH && a_val == LOW) {
    // Turning!
    if (b == HIGH) {
      angle -= DEGREES_PER_CLICK;
    }
    else {
      angle += DEGREES_PER_CLICK;
    }

    if (angle < 0) {
      angle += 360;
    }
    angle = angle % 360;
  }

  a_val = a;
  b_val = b;
}

/**
 * Returns the current angle of the knob
 * @return {int} The angle, in degrees
 */
int TactileConsole::getAngle()
{
  return angle;
}

/**
 * Convert degrees to radians
 */
float TactileConsole::d2r(float degrees) {
  return degrees * (PI / 180);
}

/** clamps a value between min and max
 */
float TactileConsole::clamp(float val, float minimum, float maximum) {
  return min(max(val, minimum), maximum);
}