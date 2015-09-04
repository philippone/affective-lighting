/*
  Model.h - Library for handling inc/out messages
*/
#ifndef Model_h
#define Model_h
#include <Arduino.h>



class Model {

  private:
    int maxBrightness = 32;

    // ClockMode
    byte clockDesign = 2;




    // debug
    boolean debugMode = false;


    // debug variables
    float debug_tmp = 14.0;

  public:
    boolean isInDebug();
    int getMaxBrightness();

    // ClockMode
    byte getClockDesign();

    // debug methods
    float getDebugTmp();

};


#endif
