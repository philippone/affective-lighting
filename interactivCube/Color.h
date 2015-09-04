/*
  Color.h - ColorHolder
*/
#ifndef Color_h
#define Color_h
#include <Arduino.h>

class Color {

  private:
    
    
  public:
  byte r,g,b;
  Color();
  Color(byte r, byte g, byte b);

  boolean equals(Color c);
};

#endif
