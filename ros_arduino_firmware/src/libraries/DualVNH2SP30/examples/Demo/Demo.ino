#include "DualVNH2SP30.h"

DualVNH2SP30 md;

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while(1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while(1);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual VNH2SP30 Motor Shield");
  md.init();
}

void loop()
{
  for (int i = 0; i <= 255; i++)
  {
    md.setM1Speed(i);
    //stopIfFault();
    Serial.println(i);
    if (i%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(10);
  }
  
  for (int i = 255; i >= -255; i--)
  {
    md.setM1Speed(i);
    //stopIfFault();
    Serial.println(i);
    if (i%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(10);
  }
  
  for (int i = -255; i <= 0; i++)
  {
    md.setM1Speed(i);
    //stopIfFault();
    Serial.println(i);
    if (i%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(10);
  }

  for (int i = 0; i <= 255; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    Serial.println(i);
    if (i%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
    delay(10);
  }
  
  for (int i = 255; i >= -255; i--)
  {
    md.setM2Speed(i);
    stopIfFault();
    Serial.println(i);
    if (i%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
    delay(10);
  }
  
  for (int i = -255; i <= 0; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    Serial.println(i);
    if (i%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
    delay(10);
  }
}
