#include "Person.h"


Person::Person() {
  id = -1L;
  color = Color(0,0,0);
}


Person::Person(long pId, Color c) {
  id = pId;
  color = c;
}


long Person::getId() {
  return id;
}

void Person::setId(long pId) {
  id = pId;
}

Color Person::getColor() {
  return color;
}

void Person::setColor(Color c) {
  color = c;
}

