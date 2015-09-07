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
    String getValue(String data, char separator, int index);
  
  public:
    MsgHandler(Model* model);
    void init(Stream* s);
    void checkInput(); // check if input is available and handles it
    void sendMsg(String msg);
    void sendConnectionHandshake();
    
    void hanldeHandshakeClock(String message);
    void addDebugStream(Stream* debugStream);

    void debugMsg(String msg);
};


#endif
