/*
  PresenceMode.h - Library for computing/controlling presencemode
*/
#ifndef PresenceMode_h
#define PresenceMode_h
#include "ledController.h"
#include "Model.h"

class PresenceMode {
  private:
    LedController* ledController;
    Model* model;
  
  public:
    PresenceMode(LedController* contr, Model* m);
    void execute();  
    void rotate(int index, int rotations);
  };


  
#endif
