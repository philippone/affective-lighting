/*
  ClockMode.h - Library for computing/controlling clockmode
*/
#ifndef ClockMode_h
#define ClockMode_h
#include <Arduino.h>
#include <Time.h>

#include "ledController.h"
#include "Model.h"
#include "Color.h"

class ClockMode {

  private:
    LedController* ledController;
    Model* model;
    Color c1 = Color(0,255,0);
    Color ledOff = Color(0,0,0);
    //byte *indicesToSet;
    void rotate(int index, int rotations);

  public:
    ClockMode(LedController* contr, Model* m);

    void execute(byte clockDesign);

    //hours
    void setHours1(byte startIndex, byte number, byte ledPanelIndex, Color cHour);
    void setHoursClock3(byte hours, byte ledPanelIndex, Color cHour);
    void setHours4(byte sIndex, byte hours, byte ledPanelIndex, Color c1, Color c2); 
    
    //minutes have to be between 0-59
    void setMinutesClock1(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark);
    void setMinutesClock2(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark);
    void setMinutesClock3(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark);
    void setTimeClock4(byte hours, byte minutes, byte ledPanelIndex, Color c1, Color c2, Color cCorner);
};




#endif
