
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#include "ModeManager.h";
#include "LedController.h";
#include "Model.h";
#include "MsgHandler.h";

ModeManager modeMng;
LedController ledController(256, 6);
Model model;
MsgHandler msgHandler(&model);

int mode;
unsigned long timer0;
#define interval 500
// the interval in mS 
int passed;


void setup() {
    Serial.begin(9600);
    
    // init gyro
    // klappt nicht im consturctor von ModeManager, warum auch immer????
    modeMng.initGyro();
    Serial.println(modeMng.isGyroConnected() ? "MPU6050 connection successful" : "MPU6050 connection failed");



}

void loop() {
  passed = millis()-timer0;
  //execute our code every interval (time in milliseconds)
  if (passed > interval) {
    timer0 = millis();
    mode = modeMng.getCurrentMode();
   
    /*
    Serial.println();
    Serial.print("Mode: ");
    Serial.print(mode);
    Serial.print(" ax: ");
    Serial.print(modeMng.getAccelX());
    Serial.print(" ay: ");
    Serial.print(modeMng.getAccelY());
    Serial.print(" az: ");
    Serial.print(modeMng.getAccelZ());
    */
    


    //switch over all modes
    if(mode == 1){
      ledController.displayColor(Color(0,16,0));
      }
    else if (mode == 2){
      ledController.displayColor(Color(0,16,16));
      }
    else if (mode == 3){
      ledController.displayColor(Color(16,16,0));
      }
    else if (mode == 4){
      ledController.displayColor(Color(16,0,16));
      }
    else if (mode == 5){
      ledController.displayColor(Color(0,0,16));
      }
    else if (mode == 6){
      ledController.displayColor(Color(16,0,0));
      }
    
  }
}

