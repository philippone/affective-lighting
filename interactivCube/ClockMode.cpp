#include "ClockMode.h"

//initialize with a value higher as the highest possible index
  byte indicesToSet[13];


  
ClockMode::ClockMode(LedController* contr, Model* m) {
  ledController = contr;
  model = m;
    
  /*
  c1 =new Color(0,255,0);
  c2 =new Color(255,0,0);
  c3 =new Color(0,0,255);
  c4 =new Color(255, 0, 255);*/
  }

  void ClockMode::setNumber(byte sIndex, byte number, byte ledPanelIndex) {
    //reset array
    for(int i=0;i<13;i++){
      indicesToSet[i]=64;
    }
   
    switch (number){
      case 0:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+8;
        indicesToSet[4]=sIndex+10;
        indicesToSet[5]=sIndex+16;
        indicesToSet[6]=sIndex+18;
        indicesToSet[7]=sIndex+24;
        indicesToSet[6]=sIndex+25;
        indicesToSet[7]=sIndex+26;
      break;
      
      case 1:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+8;
        indicesToSet[2]=sIndex+16;
        indicesToSet[3]=sIndex+24;
        indicesToSet[4]=sIndex+32;
      break;

      case 2:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+10;
        indicesToSet[4]=sIndex+16;
        indicesToSet[5]=sIndex+17;
        indicesToSet[6]=sIndex+18;
        indicesToSet[7]=sIndex+24;
        indicesToSet[8]=sIndex+32;
        indicesToSet[9]=sIndex+33;
        indicesToSet[10]=sIndex+34;
      break;

      case 3:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+10;
        indicesToSet[4]=sIndex+16;
        indicesToSet[5]=sIndex+17;
        indicesToSet[6]=sIndex+18;
        indicesToSet[7]=sIndex+26;
        indicesToSet[6]=sIndex+32;
        indicesToSet[7]=sIndex+33;
        indicesToSet[8]=sIndex+34;
      break;

      case 4:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+8;
        indicesToSet[2]=sIndex+10;
        indicesToSet[3]=sIndex+16;
        indicesToSet[4]=sIndex+17;
        indicesToSet[5]=sIndex+18;
        indicesToSet[6]=sIndex+26;
      break;

      case 5:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+8;
        indicesToSet[4]=sIndex+16;
        indicesToSet[5]=sIndex+17;
        indicesToSet[6]=sIndex+18;
        indicesToSet[7]=sIndex+26;
        indicesToSet[6]=sIndex+32;
        indicesToSet[7]=sIndex+33;
        indicesToSet[8]=sIndex+34;
      break;

      case 6:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+10;
        indicesToSet[4]=sIndex+16;
        indicesToSet[5]=sIndex+17;
        indicesToSet[6]=sIndex+18;
        indicesToSet[7]=sIndex+24;
        indicesToSet[8]=sIndex+26;
        indicesToSet[9]=sIndex+32;
        indicesToSet[10]=sIndex+33;
        indicesToSet[11]=sIndex+34;
      break;
      
      case 7:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+10;
        indicesToSet[4]=sIndex+18;
        indicesToSet[5]=sIndex+26;
        indicesToSet[6]=sIndex+34;
      break;
      
      case 8:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+8;
        indicesToSet[4]=sIndex+10;
        indicesToSet[5]=sIndex+16;
        indicesToSet[6]=sIndex+17;
        indicesToSet[7]=sIndex+18;
        indicesToSet[8]=sIndex+24;
        indicesToSet[9]=sIndex+26;
        indicesToSet[10]=sIndex+32;
        indicesToSet[11]=sIndex+33;
        indicesToSet[12]=sIndex+34;
      break;

      case 9:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+1;
        indicesToSet[2]=sIndex+2;
        indicesToSet[3]=sIndex+8;
        indicesToSet[4]=sIndex+10;
        indicesToSet[5]=sIndex+16;
        indicesToSet[6]=sIndex+17;
        indicesToSet[7]=sIndex+18;
        indicesToSet[8]=sIndex+26;
        indicesToSet[9]=sIndex+32;
        indicesToSet[10]=sIndex+33;
        indicesToSet[11]=sIndex+34;
      break;
      }

    for(int i=0;i<13;i++){
      if(indicesToSet[i] < 64){
        ledController->displayPinOnMatrix(ledPanelIndex, indicesToSet[i], c1); 
         Serial.print("Index set: ");
        Serial.println(indicesToSet[i]);
      } 
    }
  }

//minutes have to be between 0-59
  void ClockMode::setMinutesClock1(byte minutes, byte  ledPanelIndex){
    byte number = floor(minutes/3.5f);
    
    int minuteArray[17] = {6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48};
    for (int i=0; i<=number; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], c1);
    }
    
    for (int i=number+1; i<=17; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], ledOff);
    }
  }

  //minutes have to be between 0-59
  void ClockMode::setMinutesClock2(byte minutes, byte  ledPanelIndex){
    byte number = floor(minutes/10);
    
    int minuteArray[6] = {49,50,51,52,53,54};
    for (int i=0; i<=number; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], c1);
    }
    
    for (int i=number+1; i<=6; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], ledOff);
    }
  }
