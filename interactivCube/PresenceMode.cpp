#include "PresenceMode.h"

PresenceMode::PresenceMode(LedController* contr, Model* m) {
  ledController = contr;
  model = m;
}


void PresenceMode::execute(){

  delay(50);

  int startIndices[] = {27, 0 , 54, 6, 48, 30, 24, 3, 51};

  Person* persons = model->getPersonArray();

  persons[2].setId(2L);
  persons[2].setColor(Color(16, 0, 16));

  int k = 0;
  for(int i = 0; i < 9 ; i++){

    if(persons[i].getId() != -1L){
        k++;
    }
  }

  int startIndex = ((k+1) % 2);

  k = 0;
  for(int i = 0; i < 9 ; i++){

    if(persons[i].getId() != -1L){

      int indication_start_corner = startIndices[k + startIndex];
      int led_positions[] = {indication_start_corner, indication_start_corner + 1, indication_start_corner + 8 , indication_start_corner + 9};

      for(int j = 0; j < 4 ; j++){

        ledController->displayPinOnMatrix(1, led_positions[j], Color(16, 0, 16));  
      
      }
      
      k++;
    } 
  }

  ledController->showMatrix();
}  

