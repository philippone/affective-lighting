#include "DiscoMode.h"

byte discoIndicesToSet[8];
byte randomArray[8] = {0,1,2,3,4,5,6,7};
byte fixedArray[8] = {3,4,2,5,1,6,0,7};
int sensorValue = 0;  // variable to store the value coming from the sensor
int volumeLevel = 0;

Color cD =  Color(0, 16, 0);
Color cM = Color(16, 14, 3);
Color cU =  Color(16, 0, 0);

DiscoMode::DiscoMode(int p, LedController* contr, Model* m, MsgHandler* mHandler) {
  pin = p;  //default: A2
  ledController = contr;
  model = m;
  msgHandler = mHandler;
}

void DiscoMode::execute(){
  // read the value from the sensor:
  sensorValue = analogRead(pin);
  if (sensorValue < 1023){
      if(sensorValue < 128){
          volumeLevel = 8;
        }
      else if(sensorValue >= 128 && sensorValue < 256){
          volumeLevel = 7;        
        }
      else if(sensorValue >= 256 && sensorValue < 384){
          volumeLevel = 6;        
        }
      else if(sensorValue >= 384 && sensorValue < 512){
          volumeLevel = 5;        
        }
      else if(sensorValue >= 512 && sensorValue < 640){
          volumeLevel = 4;        
        }
      else if(sensorValue >= 640 && sensorValue < 768){
          volumeLevel = 3;        
        }
      else if(sensorValue >= 768 && sensorValue < 896){
          volumeLevel = 2;        
        }
      else if(sensorValue >= 896 && sensorValue < 1023){
          volumeLevel = 1;        
        }
    }

    
  getRandomArray(&randomArray[0]);
  //iterate over all sides
  for (int sideIndex = 1; sideIndex <= 4; sideIndex++){
    //set highest bar (main bar)
    setBar(sideIndex, randomArray[0], volumeLevel, cD, cM, cU);

    byte tempVolumeLevel = volumeLevel;
    byte helperByte = 0;
    //set remaining bars (iterate over the remaining rows)
      for (int rowIndex = 1; rowIndex < 8; rowIndex++){
        if(helperByte%2==0){
          helperByte++;
          tempVolumeLevel--;
        }
        setBar(sideIndex, randomArray[rowIndex], tempVolumeLevel, cD, cM, cU);
      }
  }
  //show everything
  ledController->showMatrix();
}


void DiscoMode::execute2(){
  // read the value from the sensor:
  sensorValue = analogRead(pin);
  if (sensorValue < 1023){
      if(sensorValue < 128){
          volumeLevel = 8;
          ledController->displayPinOnMatrix(2, 7, cU);
        }
      else if(sensorValue >= 128 && sensorValue < 256){
          volumeLevel = 7;        
          ledController->displayPinOnMatrix(2, 6, cU);
        }
      else if(sensorValue >= 256 && sensorValue < 384){
          volumeLevel = 6;
          ledController->displayPinOnMatrix(2, 5, cU);        
        }
      else if(sensorValue >= 384 && sensorValue < 512){
          volumeLevel = 5;        
          ledController->displayPinOnMatrix(2, 4, cU);
        }
      else if(sensorValue >= 512 && sensorValue < 640){
          volumeLevel = 4;        
          ledController->displayPinOnMatrix(2, 3, cU);
        }
      else if(sensorValue >= 640 && sensorValue < 768){
          volumeLevel = 3;        
          ledController->displayPinOnMatrix(2, 2, cU);
        }
      else if(sensorValue >= 768 && sensorValue < 896){
          volumeLevel = 2;        
          ledController->displayPinOnMatrix(2, 1, cU);
        }
      else if(sensorValue >= 896 && sensorValue < 1023){
          volumeLevel = 1;      
          ledController->displayPinOnMatrix(2, 0, cU);  
        }
    }
/*
  //iterate over all sides
  for (int sideIndex = 1; sideIndex <= 4; sideIndex++){
    //set highest bar2 (main bar2)
    setBar(sideIndex, fixedArray[0], volumeLevel, cD, cM, cU);
    setBar(sideIndex, fixedArray[1], volumeLevel, cD, cM, cU);

    byte tempVolumeLevel = volumeLevel;
    byte helperByte = 0;
    //set remaining bars (iterate over the remaining rows)
      for (int rowIndex = 2; rowIndex < 8; rowIndex++){
        if(helperByte%2==0){
          helperByte++;
          tempVolumeLevel--;
        }
        setBar(sideIndex, fixedArray[rowIndex], tempVolumeLevel, cD, cM, cU);
      }
  }*/
  //show everything
  ledController->showMatrix();
}


//create random order of 0-8
void DiscoMode::getRandomArray(byte* numberArray){

  const size_t n = sizeof(numberArray) / sizeof(numberArray[0]);

  for (size_t i = 0; i < n - 1; i++)
  {
    size_t j = random(1, n - i);

    int t = numberArray[i];
    numberArray[i] = numberArray[j];
    numberArray[j] = t;
  }
}


void DiscoMode::setBar(int ledPanelIndex, int rowIndex, int height, Color cDown, Color cMid, Color cUp){
  //reset Array
  for (int i = 0; i < 8; i++) {
    discoIndicesToSet[i] = 64;
  }
 
  if(height >0){
    //get indices to set
    for (int i = height; i <= 0; i--) {
      discoIndicesToSet[i] = rowIndex + ((i-1)*8);
    }


    //set red parts of bars
    ledController->displayPinOnMatrix(ledPanelIndex, discoIndicesToSet[0], cUp);
  
    //set yellow parts of bars
    for (int i = 1; i < 5; i++) {
      if (discoIndicesToSet[i] < 64) {
        ledController->displayPinOnMatrix(ledPanelIndex, discoIndicesToSet[i], cMid);
      }
    }

    //set green parts of bars
    for (int i = 5; i < 8; i++) {
      if (discoIndicesToSet[i] < 64) {
        ledController->displayPinOnMatrix(ledPanelIndex, discoIndicesToSet[i], cDown);
      }
    }
  }
}
