#include "NightLightMode.h"

NightLightMode::NightLightMode(int p, LedController* ledCntr, Model* m) {
  pin = p;
  ledController = ledCntr;
  model = m;
  
}


void NightLightMode::execute() {

    int bla = 24; 
    // measure the brightness in the room
    int brightness = analogRead(pin);

    // Get the user controlled color from the Model
    // Color c = new Color(0,0,0);
    // TODO: impl in Model : c = m->getNightlightColor();

    // Get the user controlled NightightMode from the Model
    byte nightlightMode = 0; // default
    // TODO: impl in Model : nightlightMode = m->getNightlightMode();
    
    // simply map values to percent and regulate leds
    float perc = 1024.0 / 100.0 ;
    float brightness_perc = brightness / perc;
    int monoC = (int) (brightness_perc * bla);
    Color c = Color(monoC, monoC, monoC);

    ledController->displayColor(c);
    
}
