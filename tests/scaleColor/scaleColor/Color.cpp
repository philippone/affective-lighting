#include "Color.h"



Color::Color(byte red, byte green, byte blue) {
  r = red;
  g = green;
  b = blue;
}

Color::Color(){
  r = 0;
  g = 0;
  b = 0;  
}



boolean Color::equals(Color c) {
  boolean e = true;
  if (r != c.r)
    e = false;
  if (g != c.g)
    e = false;
  if (b != c.b)
    e = false;

  return e;
}


Color Color::scale(int s){
  byte newR = floor(r / s);
  byte newG = floor(g / s);
  byte newB = floor(b / s);

  Color c = Color(newR, newG, newB);

  return c;
}

