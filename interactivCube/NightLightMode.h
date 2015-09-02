/*
  NightLightMode.h - Library for computing/controlling clockmode
*/
#ifndef NightLightMode_h
#define NightLightMode_h
#include <Arduino.h>
#include "Color.h"
#include "LedController.h"
#include "Model.h"

class NightLightMode {

  private:
    int pin;
    LedController* ledController;
    Model* model;
  
  public:
    NightLightMode(int pin, LedController* ledCntr, Model* m);
    void execute(); // get brightness value and adapt color of matrix

};

#endif
