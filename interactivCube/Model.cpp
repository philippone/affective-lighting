#include "Model.h"


int Model::getMaxBrightness() {
  return maxBrightness;
}

void Model::setMaxBrightness(int brightness) {
  maxBrightness = brightness;
}


/**Clock Mode stuff begin**/
byte Model::getClockDesign() {
  return clockDesign;
}

void Model::setClockDesign(byte design) {
  clockDesign = design;
}

/**Clock Mode stuff end**/



/**Presence Mode stuff begin **/

Person* Model::getPersonArray() {
  return persons;
}


/**
* add person == set present
*/
void Model::addPerson(long id, Color c) {
  for (int i = 0; i < 9; i++) {
    Person p = persons[i];

    if (p.getId() == -1) {
      p.setId(id);
      p.setColor(c);
      break;
    }
  }
}

/**
* remove person == set absent
*/
void Model::removePerson(long id) {
  for (int i = 9; i >= 0; i--) {
    Person p = persons[i];
    if (p.getId() == id) {
      p.setId(-1);
      p.setColor(Color(0, 0, 0));
      break;
    }
  }
}


/**Presence Mode stuff end **/

/**NightLightMode stuff begin**/

Color* Model::getNightLightColor() {
  return nightLight_baseColor;
}

void Model::setNightLightColor(Color c) {
  nightLight_baseColor->r = c.r;
  nightLight_baseColor->g = c.g;
  nightLight_baseColor->b = c.b;
}

int Model::getNightLightFacettes() {
  return nightLight_facettes;
}

void Model::setNightLightFacettes(int value) {
  nightLight_facettes = value;
}


/**NightLightMode stuff end**/

///// DEBUG ///////

boolean Model::isInDebug() {
  return debugMode;
}

void Model::setDebugMode(boolean onOff) {
  debugMode = onOff ;
}

/**Debug Mode stuff begin**/

float Model::getDebugTmp() {
  return debug_tmp;
}


/**Debug Mode stuff end **/

