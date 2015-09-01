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
  
  public:
    MsgHandler(Model* model);

};


#endif
