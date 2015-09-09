#include "Color.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  Color c = Color(15,36, 12);


  scaleColor(&c);

  Serial.println(c.r);
  Serial.println(c.g);
  Serial.println(c.b);

}

void loop() {
  // put your main code here, to run repeatedly:

}


float maxBrightness = 34;

void scaleColor(Color* c) {
  if (c->r > maxBrightness || c->g > maxBrightness || c->b > maxBrightness) {
    float  scaleFactor = 0;

    // find biggest value
    if (c->r > c->g) {
      if (c->r > c->b) {
        // red biggest
        scaleFactor = maxBrightness / c->r;
        Serial.print("scaleFacotr: ");
        Serial.println(scaleFactor);
        c->r = maxBrightness;
        c->g = (int) (c->g * scaleFactor);
        c->b = (int) (c->b * scaleFactor);
      }
    } else {
      if (c->g > c->b) {
        // green biggest value

        scaleFactor = maxBrightness / c->g;
        c->g = maxBrightness;
        c->r = c->r * scaleFactor;
        c->b = c->b * scaleFactor;


      } else {
        // blue biggest value
        scaleFactor = maxBrightness / c->b;
        c->b = maxBrightness;
        c->r = c->r * scaleFactor;
        c->g = c->g * scaleFactor;

      }
    }

  } else {
    // do nothing
    //return;
  }
}
