/*
  MsgHandler.h - Library for handling inc/out messages
*/
#ifndef MsgHandler_h
#define MsgHandler_h
#include <Arduino.h>

#include "Model.h"

class MsgHandler {

  private:
    Model* model;
    Stream* serial;
    Stream* debug;
    void handle(String message);
  
  public:
    MsgHandler(Model* model);
    void init(Stream* s);
    void checkInput(); // check if input is available and handles it
    void sendMsg(String msg);
    
    
    void addDebugStream(Stream* debugStream);
};


#endif
