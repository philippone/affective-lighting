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
#include "MsgHandler.h"

class ClockMode {

  private:
    LedController* ledController;
    Model* model;
    MsgHandler* msgHandler;
    Color c1 = Color(0,255,0);
    Color ledOff = Color(0,0,0);
    //byte *indicesToSet;
    void rotate(int index, int rotations);

  public:
    ClockMode(LedController* contr, Model* m,  MsgHandler* msgHandler);
    void execute(byte clockDesign);

    //Design 1
    void setHours1(byte startIndex, byte number, byte ledPanelIndex, Color cHour);
    void setMinutesClock1(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark);

    //Design 2
    void setMinutesClock2(byte minutes, byte  ledPanelIndex, Color cMinutes);

    //Design 3
    void setTimeClock3(byte hours, byte minutes, byte ledPanelIndex, Color cHour, Color cMinutes, Color cCorner);
    //void setHours3(byte sIndex, byte hours, byte ledPanelIndex, Color c1, Color c2); 
    
    //Design 4
    void setTimeClock4(byte hours, byte minutes, byte seconds, byte ledPanelIndex, Color cHour, Color cMinutes, Color cSeconds);
    void setBinaryClock4(int startIndex, int size, byte hours, byte ledPanelIndex, Color c);
};




#endif
