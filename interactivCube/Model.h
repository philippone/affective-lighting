/*
  Model.h - Library for handling inc/out messages
*/
#ifndef Model_h
#define Model_h
#include <Arduino.h>

#include "Color.h"
#include "Person.h"


class Model {

  private:
    int maxBrightness = 32;

    // ClockMode
    byte clockDesign = 2;

    // NightLight Mode
    Color* nightLight_baseColor = new Color(16,16,16);
    int nightLight_facettes = 32;


    // PresenceMode
    Person persons[9];

    // debug
    boolean debugMode = false;
    boolean tempDebug = false;

    // debug variables
    float debug_tmp = 14.0;

  public:
    boolean isInDebug();
    void setDebugMode(boolean onOff);
    int getMaxBrightness();
    void setMaxBrightness(int brightness);

    boolean isTempDebug();
    void setTempDebug(boolean b);
    void setTempDebugValue(float v);
    float getTempDebugValue();

    // ClockMode
    byte getClockDesign();
    void setClockDesign(byte design);

    // NightLightMode
    Color* getNightLightColor();
    void setNightLightColor(Color c);
    int getNightLightFacettes();
    void setNightLightFacettes(int value);

    // Presence Mode
    Person* getPersonArray();
    void setPersonArray(Person persons[]);
    void addPerson(long id, Color c);
    void removePerson(long id);
    void setPersonPresent(long id);
    void setPersonAbsent(long id);
    void clearPersons();

    

    // debug methods
    float getDebugTmp();

};


#endif
