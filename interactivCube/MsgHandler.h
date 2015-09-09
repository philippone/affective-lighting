/*
  MsgHandler.h - Library for handling inc/out messages
*/
#ifndef MsgHandler_h
#define MsgHandler_h
#include <Arduino.h>
#include <Time.h>

#include "Model.h"

class MsgHandler {

  private:
    Model* model;
    Stream* serial;
    Stream* debug;
    void handle(String message);
    void hanldeHandshakeClock(String message);
    void handleNightLightPrimColor(String message);
    void handleClockDesign(String message);
    
    //void handlePresencePersonArray(String message);
    void hanldePresenceAddPerson(String message);
    void handlePresenceRemovePerson(String message);
    void handlePresencePresent(String message);
    void handlePresentAbsent(String message);
    String getValue(String data, char separator, int index);
  
  public:
    MsgHandler(Model* model);
    void init(Stream* s);
    void checkInput(); // check if input is available and handles it
    void sendMsg(String msg);
    void sendConnectionHandshake();
    
    
    void addDebugStream(Stream* debugStream);

    void debugMsg(String msg);
    Stream* getSerial();
    Stream* getDebugStream();
};


#endif
