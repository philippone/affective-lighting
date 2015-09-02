#include "NightLightMode.h"
#define LED_MAX_INTENSITY = 24;

NightLightMode::NightLightMode(int p, LedController* ledCntr, Model* m) {
  pin = p;
  ledController = ledCntr;
  model = m;
  
}


void NightLightMode::execute() {

    // measure the brightness in the room
    int brightness = analogRead(p);

    // Get the user controlled color from the Model
    // Color c = new Color(0,0,0);
    // TODO: impl in Model : c = m->getNightlightColor();

    // Get the user controlled NightightMode from the Model
    byte nightlightMode = 0; // default
    // TODO: impl in Model : nightlightMode = m->getNightlightMode();
    
    // simply map values to percent and regulate leds
    float perc = 1024.0 / 100.0 
    float brightness_perc = brightness / perc;
    int monoC = (int) (brightness_perc * LED_MAX_INTENSITY);
    Color c = new Color(monoC, monoC, monoC);

    LedController->displayColor(c);
    
}
