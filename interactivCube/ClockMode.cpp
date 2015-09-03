#include "ClockMode.h"

//initialize with a value higher as the highest possible index
  byte indicesToSet[16];

  Color clock1Background = Color(12,12,12);
  Color clockMatrix[64];

  Color clock1Hours = Color(0,0,20);
  Color clock1Minutes =  Color(0,30,0);
  Color clock1MinutesDark =  Color(0,8,0);

  
ClockMode::ClockMode(LedController* contr, Model* m) {
  ledController = contr;
  model = m;
    
  /*
  c1 =new Color(0,255,0);
  c2 =new Color(255,0,0);
  c3 =new Color(0,0,255);
  c4 =new Color(255, 0, 255);*/
  }


  void ClockMode::execute(byte clockDesign){

/*       //illuminate top side
        //ledController.displayMatrix(1,clock1Background);
        //ledController.displayMatrix(3,clock1Background);
        ledController.displayColor(clock1Background);
        
        //set hours on all 4 sides
        clockMode.setHours1(0, hourFormat12(), 0, clock1Hours);
        clockMode.setHours1(0, hourFormat12(), 2, clock1Hours);
        clockMode.setHours1(0, hourFormat12(), 4, clock1Hours);
        clockMode.setHours1(0, hourFormat12(), 5, clock1Hours);

        //set minutes on all 4 sides
        clockMode.setMinutesClock1(minute(), 0, clock1Minutes, clock1MinutesDark);
        clockMode.setMinutesClock1(minute(), 2, clock1Minutes, clock1MinutesDark);
        clockMode.setMinutesClock1(minute(), 4, clock1Minutes, clock1MinutesDark);
        clockMode.setMinutesClock1(minute(), 5, clock1Minutes, clock1MinutesDark);  
        }
*/

    //illuminate top + bottom side
    ledController->displayMatrix(1,clock1Background);
    ledController->displayMatrix(3,clock1Background);

    switch (clockDesign){
    case 1:
    //initialize array with background color
    for(int i=0;i<16;i++){
      clockMatrix[i]=clock1Background;
      }

      ledController->displayColor(clock1Background);

              //set hours on all 4 sides
        setHours1(0, hourFormat12(), 0, clock1Hours);
        setHours1(0, hourFormat12(), 2, clock1Hours);
        setHours1(0, hourFormat12(), 4, clock1Hours);
        setHours1(0, hourFormat12(), 5, clock1Hours);

        //set minutes on all 4 sides
        setMinutesClock1(minute(), 0, clock1Minutes, clock1MinutesDark);
        setMinutesClock1(minute(), 2, clock1Minutes, clock1MinutesDark);
        setMinutesClock1(minute(), 4, clock1Minutes, clock1MinutesDark);
        setMinutesClock1(minute(), 5, clock1Minutes, clock1MinutesDark);  

    break;
    }

    Color* tmpM = ledController->getCurrentPixelMatrix(2);
    ledController->RotateDisplay(1, tmpM);

    ledController->displayMatrix(2, tmpM );
/*
    Adafruit_NeoPixel* pixels = ledController->getDisplay();
    uint8_t* array = pixels->getPixels();

    uint8_t value = 25;

    Color tempC(array[0], array[1], array[2]);

    ledController->displayPinInColor(0,Color(0,0,0));
*
        
ledController->showMatrix();
      delay(1000);
    ledController->displayPinInColor(0,tempC);

/*
    array[0] =0;
array[1] = 0;
array[2] = 0;
array[4] = 255;
  */  
    
    
ledController->showMatrix();
      
    }
    

  void ClockMode::setHours1(byte sIndex, byte number, byte ledPanelIndex, Color cHour) {
    //reset array
    for(int i=0;i<16;i++){
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
        indicesToSet[7]=sIndex+34;
        indicesToSet[8]=sIndex+2;
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
        indicesToSet[8]=sIndex+32;
        indicesToSet[9]=sIndex+33;
        indicesToSet[10]=sIndex+34;
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

      case 10:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+2;
        indicesToSet[2]=sIndex+3;
        indicesToSet[3]=sIndex+4;
        indicesToSet[4]=sIndex+8;
        indicesToSet[5]=sIndex+11;
        indicesToSet[6]=sIndex+13;
        indicesToSet[7]=sIndex+16;
        indicesToSet[8]=sIndex+19;
        indicesToSet[9]=sIndex+21;
        indicesToSet[10]=sIndex+24;
        indicesToSet[11]=sIndex+27;
        indicesToSet[12]=sIndex+29;
        indicesToSet[13]=sIndex+32;
        indicesToSet[14]=sIndex+35;
        indicesToSet[15]=sIndex+36;
        indicesToSet[16]=sIndex+37;
      break;

      case 11:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+2;
        indicesToSet[2]=sIndex+8;
        indicesToSet[3]=sIndex+10;
        indicesToSet[4]=sIndex+16;
        indicesToSet[5]=sIndex+18;
        indicesToSet[6]=sIndex+24;
        indicesToSet[7]=sIndex+26;
        indicesToSet[8]=sIndex+32;
        indicesToSet[9]=sIndex+34;
      break;

      case 12:
        indicesToSet[0]=sIndex;
        indicesToSet[1]=sIndex+2;
        indicesToSet[2]=sIndex+3;
        indicesToSet[3]=sIndex+4;
        indicesToSet[4]=sIndex+8;
        indicesToSet[5]=sIndex+13;
        indicesToSet[6]=sIndex+16;
        indicesToSet[7]=sIndex+19;
        indicesToSet[8]=sIndex+20;
        indicesToSet[9]=sIndex+21;
        indicesToSet[10]=sIndex+24;
        indicesToSet[11]=sIndex+27;
        indicesToSet[12]=sIndex+32;
        indicesToSet[13]=sIndex+35;
        indicesToSet[14]=sIndex+36;
        indicesToSet[15]=sIndex+37;
      break;

      default:
      break;
      }

    for(int i=0;i<16;i++){
      if(indicesToSet[i] < 64){
        ledController->displayPinOnMatrix(ledPanelIndex, indicesToSet[i], cHour); 
      } 
    }
  }

//minutes have to be between 0-59
  void ClockMode::setMinutesClock1(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark){
    byte number = floor(minutes/3.5f);
    
    int minuteArray[17] = {6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48};
    for (int i=0; i<=number; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], cMinutes);
    }
    
    for (int i=number+1; i<=17; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], cMinutesDark);
    }
  }

  //minutes have to be between 0-59
  void ClockMode::setMinutesClock2(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark){
    byte number = floor(minutes/10);
    
    int minuteArray[6] = {49,50,51,52,53,54};
    for (int i=0; i<=number; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], cMinutes);
    }
    
    for (int i=number+1; i<=6; i++){
      ledController->displayPinOnMatrix(ledPanelIndex ,minuteArray[i], cMinutesDark);
    }
  }
