/*
  Person.h - PersonHolder
*/
#ifndef Person_h
#define Person_h
#include "Color.h"

class Person {

  private:
  long id;
  Color color;
     
  public:
  Person();
  Person(long pId, Color c);

  long getId();
  void setId(long pId);

  Color getColor();
  void setColor(Color c);

};

#endif
