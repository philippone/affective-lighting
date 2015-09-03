/*
  TemperatureMode.h - Library for handling inc/out messages
*/
#ifndef TemperatureMode_h
#define TemperatureMode_h
#include <Arduino.h>

#include "LedController.h"
#include "Model.h"
#include "Color.h"


class TemperatureMode {

  private:
    int pin;
    LedController* ledController;
    Model* model;
    float getCelsius(int value);
    Color getColorForTemp(float temp);

  public:
    TemperatureMode(int p, LedController* ledC, Model* m);
    String execute();
};


#endif
