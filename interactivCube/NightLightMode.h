/*
  NightLightMode.h - Library for computing/controlling clockmode
*/
#ifndef NightLightMode_h
#define NightLightMode_h
#include <Arduino.h>

#include "LedController.h"

class NightLightMode {

  private:
    int pin;
    LedController* ledController;
  
  public:
    NightLightMode(int pin, LedController* ledCntr);
    void execute(); // get brightness value and adapt color of matrix

};

#endif
