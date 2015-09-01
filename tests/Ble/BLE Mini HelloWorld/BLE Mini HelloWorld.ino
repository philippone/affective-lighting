/*******************************************
* This example is for Arduino board listed below working with BLEMini,chating with BLE app in ipod etc.
* BLEMini's TX map the RX below and its RX map the TX below
*
* Board       RX      TX
* UNO         PIN8    PIN9  (PINs can be changed in file "document/library/AltSoftSerial/config/known_boards.h")
* MEGA2560    PIN19   PIN18 (actually use the Serial1)
* Leonardo    PIN0    PIN1  (actually use the Serial1)
*******************************************/
#include <Arduino.h>
#include <AltSoftSerial.h>

// For UNO, AltSoftSerial library is required, please get it from:
// http://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)  
  AltSoftSerial BLEMini;  
#else
  #define BLEMini Serial1
#endif

void setup()
{
    BLEMini.begin(57600); 
    Serial.begin(57600);
}

void loop()
{
  BLEMini.write('H');
  BLEMini.write('e');
  BLEMini.write('l');
  BLEMini.write('l');
  BLEMini.write('o');
  BLEMini.write(' ');
  BLEMini.write('W');
  BLEMini.write('o');
  BLEMini.write('r');
  BLEMini.write('l');
  BLEMini.write('d');
  BLEMini.write('!');
  
  delay(1000);
}
