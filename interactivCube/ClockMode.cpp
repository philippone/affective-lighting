#include "ClockMode.h"

//initialize with a value higher as the highest possible index
byte indicesToSet[16];

Color clockMatrix[64];
Color clock1Background = Color(12, 12, 12);
Color clock1Hours = Color(0, 0, 20);
Color clock1Minutes =  Color(0, 30, 0);
Color clock1MinutesDark =  Color(0, 4, 0);
Color clock2Background2 = Color(16, 14, 3);
int startIndex = 0;


ClockMode::ClockMode(LedController* contr, Model* m) {
  ledController = contr;
  model = m;

  /*
  c1 =new Color(0,255,0);
  c2 =new Color(255,0,0);
  c3 =new Color(0,0,255);
  c4 =new Color(255, 0, 255);*/
}


void ClockMode::execute(byte clockDesign) {

  int minutes = minute();
  int hours = hourFormat12();

  //illuminate top + bottom side
  ledController->displayMatrix(1, clock1Background);
  ledController->displayMatrix(3, clock1Background);

  switch (clockDesign) {
    case 1:
      //initialize array with background color
      for (int i = 0; i < 16; i++) {
        clockMatrix[i] = clock1Background;
      }

      ledController->displayColor(clock1Background);

      //set start position of the hour
      if(hours<10){
        if (hours == 1){
            startIndex = 3;
          }else{
            startIndex = 2;
          }
      }
      else{
        startIndex = 0;
      }
      
      //set hours on all 4 sides
      setHours1(startIndex, hours, 0, clock1Hours);
      setHours1(startIndex, hours, 2, clock1Hours);
      setHours1(startIndex, hours, 4, clock1Hours);
      setHours1(startIndex, hours, 5, clock1Hours);


      //set minutes on all 4 sides
      setMinutesClock1(minutes, 0, clock1Minutes, clock1MinutesDark);
      setMinutesClock1(minutes, 2, clock1Minutes, clock1MinutesDark);
      setMinutesClock1(minutes, 4, clock1Minutes, clock1MinutesDark);
      setMinutesClock1(minutes, 5, clock1Minutes, clock1MinutesDark);

      break;

    case 2:
      //initialize array with background color
      ledController->displayColor(clock1Background);
      ledController->displayPinsInColor(40,64, clock2Background2);
      ledController->displayPinsInColor((64*2)+40,(64*2)+64, clock2Background2);
      ledController->displayPinsInColor((64*4)+40,(64*4)+64, clock2Background2);
      ledController->displayPinsInColor((64*5)+40,(64*5)+64, clock2Background2);
 
      //set start position of the hour
      if(hours<10){
        if (hours == 1){
            startIndex = 6;
          }else{
            startIndex = 5;
          }
          setHours1(0, 0, 0, clock1Hours);
          setHours1(0, 0, 2, clock1Hours);
          setHours1(0, 0, 4, clock1Hours);
          setHours1(0, 0, 5, clock1Hours);
      }else{
        startIndex = 2;
      }
      
      //set hours on all 4 sides
      setHours1(startIndex, hours, 0, clock1Hours);
      setHours1(startIndex, hours, 2, clock1Hours);
      setHours1(startIndex, hours, 4, clock1Hours);
      setHours1(startIndex, hours, 5, clock1Hours);

      //set minutes on all 4 sides
      setMinutesClock2(minutes, 0, clock1Minutes, clock1MinutesDark);
      setMinutesClock2(minutes, 2, clock1Minutes, clock1MinutesDark);
      setMinutesClock2(minutes, 4, clock1Minutes, clock1MinutesDark);
      setMinutesClock2(minutes, 5, clock1Minutes, clock1MinutesDark);
      
      break;
      
    case 3:
      //initialize array with background color
      ledController->displayColor(clock1Background);

      //set hour
      setHoursClock3(hourFormat12(), 0, clock1Hours);
      setHoursClock3(hourFormat12(), 2, clock1Hours);
      setHoursClock3(hourFormat12(), 4, clock1Hours);
      setHoursClock3(hourFormat12(), 5, clock1Hours);

      //set minutes
      setMinutesClock3(minute(), 0, clock1Minutes, clock1MinutesDark);
      setMinutesClock3(minute(), 2, clock1Minutes, clock1MinutesDark);
      setMinutesClock3(minute(), 4, clock1Minutes, clock1MinutesDark);
      setMinutesClock3(minute(), 5, clock1Minutes, clock1MinutesDark);
      break;
  }

  rotate(2, 1);
  rotate(5, 2);
  rotate(4, -1);
  rotate(0, 2);


  ledController->showMatrix();

}


void ClockMode::rotate(int index, int rotations) {
  Color* tmpM2 = ledController->getCurrentPixelMatrix(index);
  ledController->RotateDisplay(rotations, tmpM2);
  ledController->displayMatrix(index, tmpM2 );
  free(tmpM2);
}

void ClockMode::setHours1(byte sIndex, byte number, byte ledPanelIndex, Color cHour) {
  //reset array
  for (int i = 0; i < 17; i++) {
    indicesToSet[i] = 64;
  }

  switch (number) {
    case 0:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 8;
      indicesToSet[4] = sIndex + 10;
      indicesToSet[5] = sIndex + 16;
      indicesToSet[6] = sIndex + 18;
      indicesToSet[7] = sIndex + 24;
      indicesToSet[8] = sIndex + 26;
      indicesToSet[9] = sIndex + 32;
      indicesToSet[10] = sIndex + 33;
      indicesToSet[11] = sIndex + 34;
      break;

    case 1:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 8;
      indicesToSet[2] = sIndex + 16;
      indicesToSet[3] = sIndex + 24;
      indicesToSet[4] = sIndex + 32;
      break;

    case 2:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 10;
      indicesToSet[4] = sIndex + 16;
      indicesToSet[5] = sIndex + 17;
      indicesToSet[6] = sIndex + 18;
      indicesToSet[7] = sIndex + 24;
      indicesToSet[8] = sIndex + 32;
      indicesToSet[9] = sIndex + 33;
      indicesToSet[10] = sIndex + 34;
      break;

    case 3:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 10;
      indicesToSet[4] = sIndex + 16;
      indicesToSet[5] = sIndex + 17;
      indicesToSet[6] = sIndex + 18;
      indicesToSet[7] = sIndex + 26;
      indicesToSet[8] = sIndex + 32;
      indicesToSet[9] = sIndex + 33;
      indicesToSet[10] = sIndex + 34;
      break;

    case 4:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 8;
      indicesToSet[2] = sIndex + 10;
      indicesToSet[3] = sIndex + 16;
      indicesToSet[4] = sIndex + 17;
      indicesToSet[5] = sIndex + 18;
      indicesToSet[6] = sIndex + 26;
      indicesToSet[7] = sIndex + 34;
      indicesToSet[8] = sIndex + 2;
      break;

    case 5:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 8;
      indicesToSet[4] = sIndex + 16;
      indicesToSet[5] = sIndex + 17;
      indicesToSet[6] = sIndex + 18;
      indicesToSet[7] = sIndex + 26;
      indicesToSet[8] = sIndex + 32;
      indicesToSet[9] = sIndex + 33;
      indicesToSet[10] = sIndex + 34;
      break;

    case 6:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 8;
      indicesToSet[4] = sIndex + 16;
      indicesToSet[5] = sIndex + 17;
      indicesToSet[6] = sIndex + 18;
      indicesToSet[7] = sIndex + 24;
      indicesToSet[8] = sIndex + 26;
      indicesToSet[9] = sIndex + 32;
      indicesToSet[10] = sIndex + 33;
      indicesToSet[11] = sIndex + 34;
      break;

    case 7:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 10;
      indicesToSet[4] = sIndex + 18;
      indicesToSet[5] = sIndex + 26;
      indicesToSet[6] = sIndex + 34;
      break;

    case 8:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 8;
      indicesToSet[4] = sIndex + 10;
      indicesToSet[5] = sIndex + 16;
      indicesToSet[6] = sIndex + 17;
      indicesToSet[7] = sIndex + 18;
      indicesToSet[8] = sIndex + 24;
      indicesToSet[9] = sIndex + 26;
      indicesToSet[10] = sIndex + 32;
      indicesToSet[11] = sIndex + 33;
      indicesToSet[12] = sIndex + 34;
      break;

    case 9:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 1;
      indicesToSet[2] = sIndex + 2;
      indicesToSet[3] = sIndex + 8;
      indicesToSet[4] = sIndex + 10;
      indicesToSet[5] = sIndex + 16;
      indicesToSet[6] = sIndex + 17;
      indicesToSet[7] = sIndex + 18;
      indicesToSet[8] = sIndex + 26;
      indicesToSet[9] = sIndex + 32;
      indicesToSet[10] = sIndex + 33;
      indicesToSet[11] = sIndex + 34;
      break;

    case 10:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 2;
      indicesToSet[2] = sIndex + 3;
      indicesToSet[3] = sIndex + 4;
      indicesToSet[4] = sIndex + 8;
      indicesToSet[5] = sIndex + 10;
      indicesToSet[6] = sIndex + 12;
      indicesToSet[7] = sIndex + 16;
      indicesToSet[8] = sIndex + 18;
      indicesToSet[9] = sIndex + 20;
      indicesToSet[10] = sIndex + 24;
      indicesToSet[11] = sIndex + 26;
      indicesToSet[12] = sIndex + 28;
      indicesToSet[13] = sIndex + 32;
      indicesToSet[14] = sIndex + 34;
      indicesToSet[15] = sIndex + 35;
      indicesToSet[16] = sIndex + 36;
      break;

    case 11:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 2;
      indicesToSet[2] = sIndex + 8;
      indicesToSet[3] = sIndex + 10;
      indicesToSet[4] = sIndex + 16;
      indicesToSet[5] = sIndex + 18;
      indicesToSet[6] = sIndex + 24;
      indicesToSet[7] = sIndex + 26;
      indicesToSet[8] = sIndex + 32;
      indicesToSet[9] = sIndex + 34;
      break;

    case 12:
      indicesToSet[0] = sIndex;
      indicesToSet[1] = sIndex + 2;
      indicesToSet[2] = sIndex + 3;
      indicesToSet[3] = sIndex + 4;
      indicesToSet[4] = sIndex + 8;
      indicesToSet[5] = sIndex + 12;
      indicesToSet[6] = sIndex + 16;
      indicesToSet[7] = sIndex + 18;
      indicesToSet[8] = sIndex + 19;
      indicesToSet[9] = sIndex + 20;
      indicesToSet[10] = sIndex + 24;
      indicesToSet[11] = sIndex + 26;
      indicesToSet[12] = sIndex + 32;
      indicesToSet[13] = sIndex + 34;
      indicesToSet[14] = sIndex + 35;
      indicesToSet[15] = sIndex + 36;
      break;

    default:
      break;
  }

  for (int i = 0; i < 17; i++) {
    if (indicesToSet[i] < 64) {
      ledController->displayPinOnMatrix(ledPanelIndex, indicesToSet[i], cHour);
    }
  }
}

void ClockMode::setHoursClock3(byte hours, byte ledPanelIndex, Color cHour){
  int indexArray[12] = {6, 15, 31, 55, 62, 59, 57, 48, 24, 8, 1};
  
  ledController->displayPinOnMatrix(ledPanelIndex, indexArray[hours-1], cHour);

  
  if(hours % 3 == 0){
    if(hours % 6 == 0)
      ledController->displayPinOnMatrix(ledPanelIndex, indexArray[hours-1]+1, cHour);
    else
      ledController->displayPinOnMatrix(ledPanelIndex, indexArray[hours-1]+8, cHour);
  }
}


//minutes have to be between 0-59
void ClockMode::setMinutesClock1(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark) {
  byte number = floor(minutes / 4);

  int minuteArray[15] = {7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56};
  for (int i = 0; i <= number; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutes);
  }

  for (int i = number + 1; i < 15; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutesDark);
  }
}

//minutes have to be between 0-59
void ClockMode::setMinutesClock2(byte minutes, byte  ledPanelIndex, Color cMinutes, Color cMinutesDark) {
  byte number = floor(minutes / 10);

  int minuteArray[6] = {49, 50, 51, 52, 53, 54};
  for (int i = 0; i <= number; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutes);
  }

  for (int i = number + 1; i < 6; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutesDark);
  }
}

void ClockMode::setMinutesClock3(byte minutes, byte ledPanelIndex, Color cMinutes, Color cMinutesDark){
  int indexArray[15] = {12, 13, 22, 30, 38, 46, 53, 52, 51, 50, 41, 33, 26, 27, 36};

  byte number = floor(minutes / 4.0f);
  
  for(int i=0; i<=number; i++){
    ledController->displayPinOnMatrix(ledPanelIndex, indexArray[i], cMinutes);
  }

  for(int i=number+1; i<=15; i++){
    ledController->displayPinOnMatrix(ledPanelIndex, indexArray[i], cMinutesDark);
  }
}

