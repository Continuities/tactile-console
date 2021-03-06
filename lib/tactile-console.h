/*
  tactile-console.h - Library for working with the Tactile Console
  @author mtownsend
  @since Oct 2018
*/

#ifndef TacCon_h
#define TacCon_h

#include "Arduino.h"

class TactileConsole
{
  public:
    TactileConsole();
    void setVibration(float degrees, float amplitude);
    void listenForRotation();
    int getAngle();
  private:
    int a_val;
    int b_val;
    int angle;
    float d2r(float degrees);
    float clamp(float val, float minimum, float maximum);
};

#endif