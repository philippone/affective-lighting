/*
  LedController.h - Library for control the led matrices
*/
#ifndef LedController_h
#define LedController_h
#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include "Color.h"


class LedController {

  private:
    int matrixPinCount;
    uint16_t ledCount;
    uint8_t ledPin;
    Adafruit_NeoPixel* pixels;
    
    
  
  public:
    LedController(uint16_t count, uint8_t pin);
    void displayPinInColor(int pin, Color c);
    void displayPinsInColor(int start, int ending, Color c);
    void displayColor(Color c);
    void displayPattern(Color matrix[]);
    void RotateDisplay(int rotationCount, Color matrix[]);
    void RotateArray(boolean clockwise, Color matrix[]);
    void displayOff();
    void displayMatrix(int index, Color c);
    void displayMatrix(int index, Color c[]);
    void displayPinOnMatrix(int m, int p, Color c);
    void showMatrix();

    Color* getCurrentPixelMatrix(int index); 

    Adafruit_NeoPixel* getDisplay();

};

#endif
