#include "PresenceMode.h"

PresenceMode::PresenceMode(LedController* contr, Model* m) {
  ledController = contr;
  model = m;
}


void PresenceMode::execute(){

  Person* persons = model->getPersonArray();

  for(int i = 0; i < 9 ; i++){

    persons[i].
    
  }

}  

