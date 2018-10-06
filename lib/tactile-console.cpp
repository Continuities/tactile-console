#include "Arduino.h"
#include "tactile-console.h"

#define NORTH 6
#define SOUTH 9
#define EAST 10
#define WEST 11

TactileConsole::TactileConsole() {}

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