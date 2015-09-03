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
void LedController::displayPattern(Color matrix[]) {
  for (int i = 0; i < 64 ; i++) {
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
  int endPin = ((index+1) * matrixPinCount);
  
  // start till endPin = on, endPin = off
  displayPinsInColor(startPin, endPin, c);
  

}

/**
* display matrix with index i in color array c
*/
void LedController::displayMatrix(int index, Color c[]) {

  // TODO: c have to be in same size as matrix (64)
  
  int startPin = (index * matrixPinCount);
  int endPin = ((index+1) * matrixPinCount);
  
  int j = 0;
  for (int i = startPin; i < endPin; i++) {
    displayPinInColor(i, c[j++]);
  }
}

/**
* colors a pin on matrix with index in color c
*/
void LedController::displayPinOnMatrix(int index, int pin, Color c) {
  int matrixStartPin = (index * matrixPinCount);
  
  displayPinInColor(matrixStartPin + pin, c);

}



// TODO
void LedController::RotateDisplay(int rotationCount, Color matrix[]) {

  boolean isClockWise = rotationCount >= 0;

  // if counterclockwise multiply -1
  if(!isClockWise){
    rotationCount *= -1;
  }
  
  for(int k = 0; k < rotationCount; k++){
    
     RotateArray(isClockWise, matrix); 
    
  } 

}

void LedController::RotateArray(boolean clockwise, Color matrix[]){
  
  int column_width = 8;
  int base_value = column_width * (column_width - 1);

  Color* rotated_matrix = new Color[matrixPinCount];
  
  for(int i = 0; i < matrixPinCount; i++){

      int new_index = 0;

       // formula depending on direction
       if(clockwise){

          // 7*w + (i/w) - (i%w) * w
          new_index = base_value + ((int) i / column_width) - ((i % column_width) * column_width);
        
       } else {

          // 7 - (i/w) + (i%w) * w;
          new_index = (column_width - 1) - ((int) i / column_width) + ((i % column_width) * column_width);
          
       }
  
      rotated_matrix[i] = matrix[new_index];
        
  }

  for(int i = 0; i < matrixPinCount; i++){

    matrix[i] = rotated_matrix[i];
  
  }

  free(rotated_matrix);

}


