/*
  DiscoMode.h - Library for computing/controlling discomode
*/
#ifndef DiscoMode_h
#define DiscoMode_h
#include "ledController.h"
#include "Model.h"
#include "Color.h"

class DiscoMode {
  private:
    int pin;
    LedController* ledController;
    Model* model;
  
  public:
    DiscoMode(int pin, LedController* contr, Model* m);
    void setBar(int matrixIndex, int rowIndex, int height, Color cDown, Color cMid, Color cUp);
    void getRandomArray(byte* numberArray);
    void execute();
    void execute2();
    
  
  };


  
#endif
