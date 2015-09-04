/*
  Model.h - Library for handling inc/out messages
*/
#ifndef Model_h
#define Model_h
#include <Arduino.h>

#include "Color.h"


class Model {

  private:
    int maxBrightness = 32;

    // ClockMode
    byte clockDesign = 2;

    // NightLight Mode
    Color nightLight_baseColor = Color(16,16,16);
    int nightLight_facettes = 32;


    // PresenceMode
    

    // debug
    boolean debugMode = false;

    // debug variables
    float debug_tmp = 14.0;

  public:
    boolean isInDebug();
    void setDebugMode(boolean onOff);
    int getMaxBrightness();
    void setMaxBrightness(int brightness);

    // ClockMode
    byte getClockDesign();
    void setClockDesign(byte design);

    // NightLightMode
    Color getNightLightColor();
    void setNightLightColor(Color c);
    int getNightLightFacettes();
    void setNightLightFacettes(int value);

    // debug methods
    float getDebugTmp();

};


#endif
