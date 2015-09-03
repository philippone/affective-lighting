#include "TemperatureMode.h"

TemperatureMode::TemperatureMode(int p, LedController* ledC, Model* m) {
  pin = p;
  ledController = ledC;
  model = m;

  
}



String TemperatureMode::execute() {

  int value = analogRead(pin);

  float celsius = getCelsius(value);

  Color c = getColorForTemp(celsius);

  return "";
}


/**
* return color for given temperature
*/
Color TemperatureMode::getColorForTemp(float temp) {
  // 2 grad = 1 pixlel in hoehe
  
  return Color(0,0,0);
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
