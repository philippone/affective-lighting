
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
#include "ClockMode.h";

ModeManager modeMng;
LedController ledController(128, 6);
Model model;
MsgHandler msgHandler(&model);
ClockMode clockMode(&ledController, &model);


Color c1 = Color(0,255,0);
Color c2 = Color(255,0,0);
Color c3 = Color(0,0,255);
Color c4 = Color(255, 0, 255);
Color mode1[64] ={
  c1,c1,c1,c3,c3,c1,c1,c1,
  c1,c3,c1,c1,c1,c1,c3,c1,
  c1,c1,c1,c1,c2,c1,c1,c1,
  c3,c1,c1,c2,c2,c1,c1,c3,
  c3,c1,c1,c1,c2,c1,c1,c3,
  c1,c1,c1,c1,c2,c1,c1,c1,
  c1,c2,c1,c1,c1,c1,c3,c1,
  c1,c1,c1,c3,c3,c1,c1,c1
};

int mode;
unsigned long timer0;
#define interval 1000
// the interval in mS 
int passed;


void setup() {
    Serial.begin(9600);
    
    // init gyro
    // klappt nicht im consturctor von ModeManager, warum auch immer????
    modeMng.initGyro();
    Serial.println(modeMng.isGyroConnected() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    timer0 = millis(); // clear the timer at the end of startup


}

void loop() {
  passed = millis()-timer0;
  //Serial.println(timer0);
  if (passed > interval) {
    timer0 = millis();
    // TODO: nur all 500 ms aufrufen
    mode = modeMng.getCurrentMode();
    //Serial.println(modeMng.getAccelX());
    Serial.println();
    Serial.print("Mode: ");
    Serial.print(mode);
    Serial.print(" ax: ");
    Serial.print(modeMng.getAccelX());
    Serial.print(" ay: ");
    Serial.print(modeMng.getAccelY());
    Serial.print(" az: ");
    Serial.print(modeMng.getAccelZ());



    //switch over all modes
    if(mode == 1){
      ledController.displayPattern(mode1);
      }
    else if (mode == 2){
      //ledController.displayColor(Color(0,16,16));
      ledController.displayPattern(mode1);
      }
    else if (mode == 3){
      //ledController.displayColor(Color(16,16,0));
      ledController.displayPattern(mode1);
      }
    else if (mode == 4){
      //ledController.displayColor(Color(16,0,16));
      ledController.displayPattern(mode1);
      }
    else if (mode == 5){
      //ledController.displayColor(Color(0,0,16));
      ledController.displayPattern(mode1);
      }
    else if (mode == 6){
      //ledController.displayColor(Color(16,0,0));
      ledController.displayPattern(mode1);
      }    
  }
}

