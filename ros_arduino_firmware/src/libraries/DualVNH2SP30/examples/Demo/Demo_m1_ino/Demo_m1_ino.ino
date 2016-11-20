#include "DualVNH2SP30.h"

DualVNH2SP30 md;


void setup()
{
  Serial.begin(115200);
  Serial.println("Dual VNH2SP30 Motor Shield");
  md.init();
}

void loop()
{
    md.setM1Speed(200);
    delay(3);

    md.setM1Speed(-200);
    delay(3);
}

