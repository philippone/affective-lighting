#include "TemperatureMode.h"

TemperatureMode::TemperatureMode(int p, LedController* ledC, Model* m) {
  pin = p;
  ledController = ledC;
  model = m;

  
}


int i = 14;

String TemperatureMode::execute() {

  if (i > 30)
  i = 14;

  int value = analogRead(pin);

  float celsius = getCelsius(value);

  //Color c = getColorForTemp(celsius);

  uint32_t c = getColorForTemp(i++);
  

  //ledController->displayColor(c);
  ledController->displayColor(c);

  ledController->getDisplay()->setBrightness(20);
  
  ledController->showMatrix();

  delay(1000);
  return "";
}


/**
* return color for given temperature
*/
uint32_t TemperatureMode::getColorForTemp(float temp) {
  // 2 grad = 1 pixlel in hoehe
  float t2 = temp - 15.0;
  float v = 170- t2*11.3;

  return ledController->Wheel(v);
}


/**
* compute analog value to celsius
*/
float TemperatureMode::getCelsius(int reading) {
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)

 return temperatureC;
  
}
