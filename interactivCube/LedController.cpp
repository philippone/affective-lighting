#include "LedController.h"


LedController::LedController(uint16_t count, uint8_t pin) {
   // init pixels
  matrixPinCount = 64;
  ledCount = count;
  ledPin = pin; 
  pixels = new Adafruit_NeoPixel(ledCount, ledPin, NEO_GRB + NEO_KHZ800);
  
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  pixels->begin(); // This initializes the NeoPixel library.
  
}


/**
* display pin  in color c
*/
void LedController::displayPinInColor(int pin, Color c) {
    pixels->setPixelColor(pin, pixels->Color(c.r,c.g,c.b)); 
    pixels->show(); // This sends the updated pixel color to the hardware.
}


/**
* display from start to ending ping in color c
*/
void LedController::displayPinsInColor(int start, int ending, Color c) {
  for(int i=start;i<ending;i++){
    pixels->setPixelColor(i, pixels->Color(c.r,c.g,c.b)); 
  }
  pixels->show(); // This sends the updated pixel color to the hardware.
}

/**
* display color on the entire cube
*/
void LedController::displayColor(Color c) {
  displayPinsInColor(0, ledCount, c);
}

/**
* set each pixel from the matrix to specific color
*/
void LedController::display(Color matrix[]) {
  for (int i = 0; i < sizeof(matrix)/sizeof(matrix[0]) ; i++) {
    Color c = matrix[i];
    pixels->setPixelColor(i, pixels->Color(c.r,c.g,c.b)); 
  }
  pixels->show(); // This sends the updated pixel color to the hardware.
}

/**
* turn all matrices off
*/
void LedController::displayOff() {
  displayColor(Color(0,0,0));
}

/**
* display matrix with index i in color c
*/
void LedController::displayMatrix(int index, Color c) {
  
   int startPin = (index * matrixPinCount);
  int endPin = ((index+1) * matrixPinCount)-1;
  
  displayPinsInColor(startPin, endPin, c);
  

}

// TODO
void LedController::RotateDisplay(int index, int rotationCount) {
}

