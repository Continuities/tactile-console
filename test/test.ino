#include <tactile-console.h>

#define BAUD 57600

TactileConsole console;

void setup() {
  Serial.begin(BAUD);
  console.setVibration(0, 0);
}

void loop() {
  console.listenForRotation();
  console.setVibration((float)console.getAngle(), 1);
}
