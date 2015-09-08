#include "NightLightMode.h"

NightLightMode::NightLightMode(int p, LedController* ledCntr, Model* m) {
  pin = p;
  ledController = ledCntr;
  model = m;
  
}

Color monoC = Color(16,16,16);

void NightLightMode::execute() {

    int bla = 24; 
    // measure the brightness in the room
    int brightness = analogRead(pin);

    // Get the user controlled color from the Model
    // Color c = new Color(0,0,0);
    // TODO: impl in Model : 
    Color c = model->getNightLightColor();
    //TDDO set brightness

    // Get the user controlled NightightMode from the Model
    byte nightlightMode = 0; // default
    // TODO: impl in Model : nightlightMode = m->getNightlightMode();
    
    // simply map values to percent and regulate leds
    float perc = 1024.0 / 100.0 ;
    float brightness_perc = brightness / perc;
    
    int monoC_new_r = (int) ((100-brightness_perc) * c.r * 0.01 );
    int monoC_new_g = (int) ((100-brightness_perc) * c.g * 0.01 );
    int monoC_new_b = (int) ((100-brightness_perc) * c.b * 0.01 );
    Color c_new = Color(monoC_new_r, monoC_new_g, monoC_new_b);

    if (!monoC.equals(c_new)) {
      monoC = c_new ;
      
      ledController->displayColor(c_new);
      ledController->showMatrix();
    }
    
    
}
