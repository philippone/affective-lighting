/*
  ClockMode.h - Library for computing/controlling clockmode
*/
#ifndef ClockMode_h
#define ClockMode_h
#include <Arduino.h>

#include "ledController.h"
#include "Model.h"

class ClockMode {

private:
  LedController* ledController;
  Model* model;

public:
  ClockMode(LedController* contr, Model* m);
  
};


#endif
