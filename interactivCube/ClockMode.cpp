#include "ClockMode.h"

//initialize with a value higher as the highest possible index
byte indicesToSet[17];

Color clockMatrix[64];

Color clockBackground = Color(5, 5, 5);

//Colors clock1
Color clock1Hours = Color(0, 0, 20);
Color clock1Minutes =  Color(0, 20, 0);

//Colors clock2
Color clock2Background2 = Color(16, 14, 3);
Color clock2Hours = Color(0, 0, 20);
Color clock2Minutes = Color(0, 20, 0);

//Colors clock3
Color clock3Hours = Color(16, 0, 0);
Color clock3Minutes = Color(0, 20, 0);
Color clock3Corners =  Color(4, 0, 0);

//Colors clock4
Color clock4Hours = Color(20, 0, 0);
Color clock4Minutes = Color(0, 20, 0);
Color clock4Seconds = Color(0, 0, 20);

int startIndex = 0;


ClockMode::ClockMode(LedController* contr, Model* m, MsgHandler* msgH) {
  ledController = contr;
  model = m;
  msgHandler = msgH;
}


void ClockMode::execute(byte clockDesign) {

  int minutes = minute();
  int hours = hourFormat12();
  int seconds = second();

  //illuminate top + bottom side
  ledController->displayMatrix(1, clockBackground);
  ledController->displayMatrix(3, clockBackground);

  switch (clockDesign) {
    // Um die Ecke bringen
    case 1:
      //initialize array with background color
      ledController->displayColor(clockBackground);

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
      setMinutesClock1(minutes, 0, clock1Minutes);
      setMinutesClock1(minutes, 2, clock1Minutes);
      setMinutesClock1(minutes, 4, clock1Minutes);
      setMinutesClock1(minutes, 5, clock1Minutes);

      break;

    // Ladebalken und Zahl
    case 2:
      //initialize array with background color
      ledController->displayColor(clockBackground);

      //set Background 2
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
          setHours1(0, 0, 0, clock2Hours);
          setHours1(0, 0, 2, clock2Hours);
          setHours1(0, 0, 4, clock2Hours);
          setHours1(0, 0, 5, clock2Hours);
      }else{
        startIndex = 2;
      }
      
      //set hours on all 4 sides
      setHours1(startIndex, hours, 0, clock2Hours);
      setHours1(startIndex, hours, 2, clock2Hours);
      setHours1(startIndex, hours, 4, clock2Hours);
      setHours1(startIndex, hours, 5, clock2Hours);

      //set minutes on all 4 sides
      setMinutesClock2(minutes, 0, clock2Minutes);
      setMinutesClock2(minutes, 2, clock2Minutes);
      setMinutesClock2(minutes, 4, clock2Minutes);
      setMinutesClock2(minutes, 5, clock2Minutes);
      
      break;

    // Zahl und 60 min
    case 3:
      setTimeClock3(hours, minutes, 0, clock3Hours, clock3Minutes, clock3Corners);
      setTimeClock3(hours, minutes, 2, clock3Hours, clock3Minutes, clock3Corners);
      setTimeClock3(hours, minutes, 4, clock3Hours, clock3Minutes, clock3Corners);
      setTimeClock3(hours, minutes, 5, clock3Hours, clock3Minutes, clock3Corners);
      break;

    //BinärUhr
    case 4:
      ledController->displayColor(clockBackground);
      setTimeClock4(hours, minutes, seconds, 0, clock4Hours, clock4Minutes, clock4Seconds);
      setTimeClock4(hours, minutes, seconds, 2, clock4Hours, clock4Minutes, clock4Seconds);
      setTimeClock4(hours, minutes, seconds, 4, clock4Hours, clock4Minutes, clock4Seconds);
      setTimeClock4(hours, minutes, seconds, 5, clock4Hours, clock4Minutes, clock4Seconds);
      break;

    //mixed design: one clock design per side
    case 5:   
  /*
  * set side 0 with clockDesign 1 : Corner Design
  */
    
    //initialize array with background color
      ledController->displayColor(clockBackground);

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

      //set minutes on all 4 sides
      setMinutesClock1(minutes, 0, clock1Minutes);

  /*
  * set side 2 with clockDesign 2 : Bar Design
  */
  
   //initialize array with background color
      ledController->displayPinsInColor((64*2)+40,(64*2)+64, clock2Background2);
 
      //set start position of the hour
      if(hours<10){
        if (hours == 1){
            startIndex = 6;
          }else{
            startIndex = 5;
          }
          setHours1(0, 0, 2, clock2Hours);
      }else{
        startIndex = 2;
      }
      
      //set hours on all 4 sides
      setHours1(startIndex, hours, 2, clock2Hours);

      //set minutes on all 4 sides
      setMinutesClock2(minutes, 2, clock2Minutes);

  /*
  * set side 4 with clockDesign 3 : 60min Design
  */
      setTimeClock3(hours, minutes, 4, clock3Hours, clock3Minutes, clock3Corners);
      
  /*
  * set side 5 with clockDesign 4 : Binary Design
  */
      setTimeClock4(hours, minutes, seconds, 5, clock4Hours, clock4Minutes, clock4Seconds);
      break;
  }

  //rotate clock view on cube side 2 and 4
  rotate(2, 1);
  rotate(4, -1);

  //show led pattern
  ledController->showMatrix();
}


//rotates led pattern on a specific matrix
void ClockMode::rotate(int index, int rotations) {
  Color* tmpM2 = ledController->getCurrentPixelMatrix(index);
  ledController->RotateDisplay(rotations, tmpM2);
  ledController->displayMatrix(index, tmpM2 );
  free(tmpM2);
}



//*************** CLOCK DESIGN 1 *************** METHODS CORNER DESIGN ***************//
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

//minutes have to be between 0-59
void ClockMode::setMinutesClock1(byte minutes, byte  ledPanelIndex, Color cMinutes) {
  byte number = floor(minutes / 4);

  int minuteArray[15] = {7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56};
  for (int i = 0; i <= number; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutes);
  }

  for (int i = number + 1; i < 15; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutes.scale(5));
  }
}



//*************** CLOCK DESIGN 2 *************** METHODS BAR DESIGN ***************//
//minutes have to be between 0-59
void ClockMode::setMinutesClock2(byte minutes, byte  ledPanelIndex, Color cMinutes) {
  byte number = floor(minutes / 10);

  int minuteArray[6] = {49, 50, 51, 52, 53, 54};
  for (int i = 0; i <= number; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutes);
  }

  for (int i = number + 1; i < 6; i++) {
    ledController->displayPinOnMatrix(ledPanelIndex , minuteArray[i], cMinutes.scale(5));
  }
}


//************* CLOCK DESIGN 3 *************** METHODS 60MIN DESIGN ***************
void ClockMode::setTimeClock3(byte hours, byte minutes, byte ledPanelIndex, Color cHour, Color cMinutes, Color cCorner){

  //set minutes
  if(minutes>=0&&minutes<7){
    ledController->displayPinsInColor((64*ledPanelIndex)+0,(64*ledPanelIndex)+ minutes + 2, cMinutes);
    ledController->displayPinsInColor((64*ledPanelIndex)+ minutes + 1,(64*ledPanelIndex)+ 64, cMinutes.scale(5));
  }
  if(minutes>6&&minutes<56){
      ledController->displayPinsInColor((64*ledPanelIndex)+ 0,(64*ledPanelIndex)+ minutes + 3, cMinutes);
      ledController->displayPinsInColor((64*ledPanelIndex)+ minutes + 2,(64*ledPanelIndex)+ 64, cMinutes.scale(5));
  }
  if(minutes>55){
      ledController->displayPinsInColor((64*ledPanelIndex)+ 0,(64*ledPanelIndex)+ minutes + 4, cMinutes);
      ledController->displayPinsInColor((64*ledPanelIndex)+ minutes+ 3,(64*ledPanelIndex)+ 64, cMinutes.scale(5));
  }


  //set corners
  ledController->displayPinOnMatrix(ledPanelIndex ,0 , cCorner);
  ledController->displayPinOnMatrix(ledPanelIndex ,7 , cCorner);
  ledController->displayPinOnMatrix(ledPanelIndex ,56 , cCorner);
  ledController->displayPinOnMatrix(ledPanelIndex ,63 , cCorner);

  bool eleven = 0;
  //set hours
  byte sIndex;
  //set hours
  if(hours<10){
    if (hours == 1){
      sIndex = 3;
    }else{
      sIndex = 2;
    }
  }else{
    sIndex = 2;
    if(hours == 11){
      eleven = 1;
      }
  }
  
  //setHours4(sIndex+16, hours, ledPanelIndex, c1, c2);
  if(eleven){
      setHours1(sIndex+16, 1, ledPanelIndex, cHour);
      setHours1(sIndex+16+3, 1, ledPanelIndex, cHour);
      eleven = 0;

  }else{
      setHours1(sIndex+16, hours, ledPanelIndex, cHour);
  }
}

//invert mode, not used
//void ClockMode::setHours3(byte sIndex, byte hours, byte ledPanelIndex, Color c1, Color c2) {
//  //reset array
//  for (int i = 0; i < 17; i++) {
//    indicesToSet[i] = 64;
//  }
//
//  switch (hours) {
//    case 0:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 8;
//      indicesToSet[4] = sIndex + 10;
//      indicesToSet[5] = sIndex + 16;
//      indicesToSet[6] = sIndex + 18;
//      indicesToSet[7] = sIndex + 24;
//      indicesToSet[8] = sIndex + 26;
//      indicesToSet[9] = sIndex + 32;
//      indicesToSet[10] = sIndex + 33;
//      indicesToSet[11] = sIndex + 34;
//      break;
//
//    case 1:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 8;
//      indicesToSet[2] = sIndex + 16;
//      indicesToSet[3] = sIndex + 24;
//      indicesToSet[4] = sIndex + 32;
//      break;
//
//    case 2:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 10;
//      indicesToSet[4] = sIndex + 16;
//      indicesToSet[5] = sIndex + 17;
//      indicesToSet[6] = sIndex + 18;
//      indicesToSet[7] = sIndex + 24;
//      indicesToSet[8] = sIndex + 32;
//      indicesToSet[9] = sIndex + 33;
//      indicesToSet[10] = sIndex + 34;
//      break;
//
//    case 3:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 10;
//      indicesToSet[4] = sIndex + 16;
//      indicesToSet[5] = sIndex + 17;
//      indicesToSet[6] = sIndex + 18;
//      indicesToSet[7] = sIndex + 26;
//      indicesToSet[8] = sIndex + 32;
//      indicesToSet[9] = sIndex + 33;
//      indicesToSet[10] = sIndex + 34;
//      break;
//
//    case 4:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 8;
//      indicesToSet[2] = sIndex + 10;
//      indicesToSet[3] = sIndex + 16;
//      indicesToSet[4] = sIndex + 17;
//      indicesToSet[5] = sIndex + 18;
//      indicesToSet[6] = sIndex + 26;
//      indicesToSet[7] = sIndex + 34;
//      indicesToSet[8] = sIndex + 2;
//      break;
//
//    case 5:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 8;
//      indicesToSet[4] = sIndex + 16;
//      indicesToSet[5] = sIndex + 17;
//      indicesToSet[6] = sIndex + 18;
//      indicesToSet[7] = sIndex + 26;
//      indicesToSet[8] = sIndex + 32;
//      indicesToSet[9] = sIndex + 33;
//      indicesToSet[10] = sIndex + 34;
//      break;
//
//    case 6:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 8;
//      indicesToSet[4] = sIndex + 16;
//      indicesToSet[5] = sIndex + 17;
//      indicesToSet[6] = sIndex + 18;
//      indicesToSet[7] = sIndex + 24;
//      indicesToSet[8] = sIndex + 26;
//      indicesToSet[9] = sIndex + 32;
//      indicesToSet[10] = sIndex + 33;
//      indicesToSet[11] = sIndex + 34;
//      break;
//
//    case 7:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 10;
//      indicesToSet[4] = sIndex + 18;
//      indicesToSet[5] = sIndex + 26;
//      indicesToSet[6] = sIndex + 34;
//      break;
//
//    case 8:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 8;
//      indicesToSet[4] = sIndex + 10;
//      indicesToSet[5] = sIndex + 16;
//      indicesToSet[6] = sIndex + 17;
//      indicesToSet[7] = sIndex + 18;
//      indicesToSet[8] = sIndex + 24;
//      indicesToSet[9] = sIndex + 26;
//      indicesToSet[10] = sIndex + 32;
//      indicesToSet[11] = sIndex + 33;
//      indicesToSet[12] = sIndex + 34;
//      break;
//
//    case 9:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 1;
//      indicesToSet[2] = sIndex + 2;
//      indicesToSet[3] = sIndex + 8;
//      indicesToSet[4] = sIndex + 10;
//      indicesToSet[5] = sIndex + 16;
//      indicesToSet[6] = sIndex + 17;
//      indicesToSet[7] = sIndex + 18;
//      indicesToSet[8] = sIndex + 26;
//      indicesToSet[9] = sIndex + 32;
//      indicesToSet[10] = sIndex + 33;
//      indicesToSet[11] = sIndex + 34;
//      break;
//
//    case 10:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 2;
//      indicesToSet[2] = sIndex + 3;
//      indicesToSet[3] = sIndex + 4;
//      indicesToSet[4] = sIndex + 8;
//      indicesToSet[5] = sIndex + 10;
//      indicesToSet[6] = sIndex + 12;
//      indicesToSet[7] = sIndex + 16;
//      indicesToSet[8] = sIndex + 18;
//      indicesToSet[9] = sIndex + 20;
//      indicesToSet[10] = sIndex + 24;
//      indicesToSet[11] = sIndex + 26;
//      indicesToSet[12] = sIndex + 28;
//      indicesToSet[13] = sIndex + 32;
//      indicesToSet[14] = sIndex + 34;
//      indicesToSet[15] = sIndex + 35;
//      indicesToSet[16] = sIndex + 36;
//      break;
//
//    case 11:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 2;
//      indicesToSet[2] = sIndex + 8;
//      indicesToSet[3] = sIndex + 10;
//      indicesToSet[4] = sIndex + 16;
//      indicesToSet[5] = sIndex + 18;
//      indicesToSet[6] = sIndex + 24;
//      indicesToSet[7] = sIndex + 26;
//      indicesToSet[8] = sIndex + 32;
//      indicesToSet[9] = sIndex + 34;
//      break;
//
//    case 12:
//      indicesToSet[0] = sIndex;
//      indicesToSet[1] = sIndex + 2;
//      indicesToSet[2] = sIndex + 3;
//      indicesToSet[3] = sIndex + 4;
//      indicesToSet[4] = sIndex + 8;
//      indicesToSet[5] = sIndex + 12;
//      indicesToSet[6] = sIndex + 16;
//      indicesToSet[7] = sIndex + 18;
//      indicesToSet[8] = sIndex + 19;
//      indicesToSet[9] = sIndex + 20;
//      indicesToSet[10] = sIndex + 24;
//      indicesToSet[11] = sIndex + 26;
//      indicesToSet[12] = sIndex + 32;
//      indicesToSet[13] = sIndex + 34;
//      indicesToSet[14] = sIndex + 35;
//      indicesToSet[15] = sIndex + 36;
//      break;
//
//    default:
//      break;
//  }
//
//  Color* tempArr = ledController->getCurrentPixelMatrix(ledPanelIndex);
//  for (int i = 0; i < 17; i++) {
//    if (indicesToSet[i] < 64) {      
//      if(tempArr[indicesToSet[i]].equals(c1)){   
//        ledController->displayPinOnMatrix(ledPanelIndex, indicesToSet[i], c2);
//      }else if(tempArr[indicesToSet[i]].equals(c2)){
//        Color cTemp =  Color(16, 0, 0);
//        ledController->displayPinOnMatrix(ledPanelIndex, indicesToSet[i], c1);
//      }
//    }
//  }
//  free(tempArr);
//}

//*************** CLOCK DESIGN 4 *************** METHODS BINARY CLOCK ***************//
void ClockMode::setTimeClock4(byte hours, byte minutes, byte seconds, byte ledPanelIndex, Color cHour, Color cMinutes, Color cSeconds){
  setBinaryClock4(10, 5, hours, ledPanelIndex, cHour);
  setBinaryClock4(25, 6, minutes, ledPanelIndex, cMinutes);
  setBinaryClock4(49, 6, seconds, ledPanelIndex, cSeconds);
}

void ClockMode::setBinaryClock4(int startIndex, int size, byte number, byte ledPanelIndex, Color c){
  int binary[size];

  for(int i=0; i<size; i++){
    binary[i] = 0;    
  }

  int helpDiv = floor(number / 2.0f);
  int helpMod = number % 2;

  
  int i=size-1;

  binary[i] = helpMod;
  
  while(helpDiv != 0){
    helpMod = helpDiv % 2;
    helpDiv = floor(helpDiv / 2.0f);
    i--;
    binary[i] = helpMod;
  }

  
  for(int i=0; i<size; i++){
    if(binary[i]==1)
        ledController->displayPinOnMatrix(ledPanelIndex, startIndex+i, c);
    else
        ledController->displayPinOnMatrix(ledPanelIndex, startIndex+i, c.scale(10));
  }
}
