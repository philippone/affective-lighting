/*
  ModeManager.h - Library for determine cube mode
*/
#ifndef ModeManager_h
#define ModeManager_h
#include <Arduino.h>

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif


class ModeManager {

  private:
    int mode;
    MPU6050 accelgyro;

    int16_t ax, ay, az;
    int16_t gx, gy, gz;

  public:
    ModeManager();
    //~ModeManager();
    void getCurrentMode();
    //double getSignalPower(int x, int y, int z);
    
    int getAccelX();
    void initGyro();

    boolean isGyroConnected();
  
};

#endif // ModeManager_h
