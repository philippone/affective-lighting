#include "PresenceMode.h"

PresenceMode::PresenceMode(LedController* contr, Model* m) {
  ledController = contr;
  model = m;
}

int lastK = 0;

void PresenceMode::execute() {

  delay(50);

  int startIndices[] = {27, 0 , 54, 6, 48, 30, 24, 3, 51};

  Person* persons = model->getPersonArray();

  int k = 0;
  for (int i = 0; i < 9 ; i++) {

    if (persons[i].getId() != -1L) {
      k++;
    }
  }

  if (k != lastK) {

    boolean isAdded = k > lastK;

    lastK = k;

    ledController->displayOff();

    int startIndex = ((k + 1) % 2);

    k = 0;
    Color lastcolor = Color(0, 0, 0);
    int* lastpositions;
    for (int i = 0; i < 9 ; i++) {

      if (persons[i].getId() != -1L) {

        int indication_start_corner = startIndices[k + startIndex];
        int led_positions[] = {indication_start_corner, indication_start_corner + 1, indication_start_corner + 8 , indication_start_corner + 9};



        for (int j = 0; j < 4 ; j++) {

          ledController->displayPinOnMatrix(0, led_positions[j], persons[i].getColor());
          ledController->displayPinOnMatrix(5, led_positions[j], persons[i].getColor());
          ledController->displayPinOnMatrix(4, led_positions[j], persons[i].getColor());
          ledController->displayPinOnMatrix(2, led_positions[j], persons[i].getColor());


        }
        k++;
        lastcolor = persons[i].getColor();
        lastpositions = led_positions;
      }
    }

    rotate(2, 1);
    rotate(4, -1);
    ledController->showMatrix();

    if (isAdded) {

      // blink 3 times
      for (int i = 0; i < 3; i++) {

        delay(300);

        rotate(2, -1);
        rotate(4, 1);

        for (int j = 0; j < 4; j++) {

          ledController->displayPinOnMatrix(0, lastpositions[j], Color());
          ledController->displayPinOnMatrix(5, lastpositions[j],  Color());
          ledController->displayPinOnMatrix(4, lastpositions[j],  Color());
          ledController->displayPinOnMatrix(2, lastpositions[j],  Color());

        }

        rotate(2, 1);
        rotate(4, -1);
        ledController->showMatrix();

        delay(300);

        rotate(2, -1);
        rotate(4, 1);

        for (int j = 0; j < 4; j++) {

          ledController->displayPinOnMatrix(0, lastpositions[j], lastcolor);
          ledController->displayPinOnMatrix(5, lastpositions[j],  lastcolor);
          ledController->displayPinOnMatrix(4, lastpositions[j],  lastcolor);
          ledController->displayPinOnMatrix(2, lastpositions[j],  lastcolor);

        }

        rotate(2, 1);
        rotate(4, -1);
        ledController->showMatrix();

      }

    }
  }

}

//rotates led pattern on a specific matrix
void PresenceMode::rotate(int index, int rotations) {
  Color* tmpM2 = ledController->getCurrentPixelMatrix(index);
  ledController->RotateDisplay(rotations, tmpM2);
  ledController->displayMatrix(index, tmpM2 );
  free(tmpM2);
}

