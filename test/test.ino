#include <tactile-console.h>

TactileConsole console;

void setup() {
}

void loop() {
  for (int angle = 0; angle < 360; angle += 1) {
    console.setVibration((float)angle, 0.5);
    delay(30);
  }
}
