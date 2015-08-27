// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#include "ModeManager.h";

ModeManager modeMng;


void setup() {
    Serial.begin(9600);
    
    // init gyro
    // klappt nicht im consturctor von ModeManager, warum auch immer????
    modeMng.initGyro();
    Serial.println(modeMng.isGyroConnected() ? "MPU6050 connection successful" : "MPU6050 connection failed");


}

void loop() {
  
  // TODO: nur all 500 ms aufrufen
  modeMng.getCurrentMode();
  //Serial.println(modeMng.getAccelX());

}

