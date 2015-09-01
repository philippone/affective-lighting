#include "LedController.h"


LedController::LedController(uint16_t count, uint8_t pin) {
   // init pixels
  ledCount = count;
  ledPin = pin; 
  pixels = new Adafruit_NeoPixel(ledCount, ledPin, NEO_GRB + NEO_KHZ800);
  
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  pixels->begin(); // This initializes the NeoPixel library.
  
}
    
void LedController::displayColor(Color c) {
  
  for(int i=0;i<ledCount;i++){
    pixels->setPixelColor(i, pixels->Color(c.r,c.g,c.b)); 
    pixels->show(); // This sends the updated pixel color to the hardware.

  }
}

void LedController::display(Color matrix[]) {
  
  for (int i = 0; i < sizeof(matrix)/sizeof(matrix[0]) ; i++) {
    Color c = matrix[i];
    pixels->setPixelColor(i, pixels->Color(c.r,c.g,c.b)); 
    pixels->show(); // This sends the updated pixel color to the hardware.
  }

}


void LedController::RotateDisplay(int index, int rotationCount) {

}
