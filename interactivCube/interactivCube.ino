
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Time.h>

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
#include "NightLightMode.h";
#include "TemperatureMode.h";

ModeManager modeMng;
LedController ledController(384, 6);
Model model;
MsgHandler msgHandler(&model);
ClockMode clockMode(&ledController, &model,&msgHandler);
NightLightMode nightLightMode(3, &ledController, &model);
TemperatureMode temperatureMode(0, &ledController, &model);


Color c2 = Color(255,0,0);
Color c3 = Color(0,0,255);
Color c4 = Color(255, 0, 255);
/*Color mode1[64] ={
  c1,c1,c1,c3,c3,c1,c1,c1,
  c1,c3,c1,c1,c1,c1,c3,c1,
  c1,c1,c1,c1,c2,c1,c1,c1,
  c3,c1,c1,c2,c2,c1,c1,c3,
  c3,c1,c1,c1,c2,c1,c1,c3,
  c1,c1,c1,c1,c2,c1,c1,c1,
  c1,c2,c1,c1,c1,c1,c3,c1,
  c1,c1,c1,c3,c3,c1,c1,c1
};*/

int mode = 3;
unsigned long timer0;
#define interval 1000
// the interval in mS 
int passed;

byte clockDesign = 5;


void setup() {
  
    Serial.begin(9600);
    //Serial1.begin(9600);
    msgHandler.init(&Serial);
    msgHandler.addDebugStream(&Serial);
    
    // testmsg
    delay(100);
    msgHandler.sendConnectionHandshake();
    
    // init gyro
    modeMng.initGyro();
    Serial.println(modeMng.isGyroConnected() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    setTime(9,45,55,2,9,15);

    //TODO: set which clock design is used
}


void loop() {
  // check if input is available
  msgHandler.checkInput();
  
  passed = millis()-timer0;
  //Serial.println(timer0);
  //executes our code every interval (in milliseconds)
  if (passed > interval) {
    timer0 = millis();
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

  }
    //switch over all modes
    
    // Temperatur
    if(mode == 0){
      //ledController.displayPattern(mode1);
      temperatureMode.execute();
      }
    // Anwesenheit
    else if (mode == 1){
      //ledController.displayColor(Color(0,16,16));
      //ledController.displayPattern(mode1);
      }
    // Nachtlicht
    else if (mode == 2){
      //ledController.displayColor(Color(16,16,0));
      //ledController.showMatrix();
      //ledController.displayPattern(mode1);
      nightLightMode.execute();
      }
   // Uhr
   else if (mode == 3){
      //ledController.displayColor(Color(16,0,16));
      clockMode.execute(clockDesign);

      }
    // Standby
    else if (mode == 4){
      //ledController.displayColor(Color(0,0,16));
      ledController.displayOff();
      }
    // Disco, Disco, Baby
    else if (mode == 5){
      //ledController.displayColor(Color(16,0,0));
      //ledController.displayPattern(mode1);
      }    

}

