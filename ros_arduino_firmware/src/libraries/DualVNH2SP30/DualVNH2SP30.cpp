#include "DualVNH2SP30.h"

// Constructors ////////////////////////////////////////////////////////////////

DualVNH2SP30::DualVNH2SP30()
{
  //Pin map
  _INA1 = 7;
  _INB1 = 8;
  _EN1DIAG1 = 12;
  _CS1 = A1;
  _INA2 = 13;
  _INB2 = 4;
  _EN2DIAG2 = 6;
  _CS2 = A0;
}



DualVNH2SP30::DualVNH2SP30(unsigned char INA1, unsigned char INB1, unsigned char EN1DIAG1, unsigned char CS1, 
                                               unsigned char INA2, unsigned char INB2, unsigned char EN2DIAG2, unsigned char CS2)
{
  //Pin map
  //PWM1 and PWM2 cannot be remapped because the library assumes PWM is on timer1
  _INA1 = INA1;
  _INB1 = INB1;
  _EN1DIAG1 = EN1DIAG1;
  _CS1 = CS1;
  _INA2 = INA2;
  _INB2 = INB2;
  _EN2DIAG2 = EN2DIAG2;
  _CS2 = CS2;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualVNH2SP30::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_INA1,OUTPUT);
  pinMode(_INB1,OUTPUT);
  pinMode(_PWM1,OUTPUT);
  pinMode(_EN1DIAG1,INPUT);
  pinMode(_CS1,INPUT);
  pinMode(_INA2,OUTPUT);
  pinMode(_INB2,OUTPUT);
  pinMode(_PWM2,OUTPUT);
  pinMode(_EN2DIAG2,INPUT);
  pinMode(_CS2,INPUT);
  //#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  // Timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 255
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 255 (top) = 20kHz
  //TCCR1A = 0b10100000;
  //TCCR1B = 0b00010001;
  //ICR1 = 255;
  //#endif
}
// Set speed for motor 1, speed is a number betwenn -255 and 255
void DualVNH2SP30::setM1Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 255)  // Max PWM dutycycle
    speed = 255;
  //#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  //OCR1A = speed;
  //Serial.println("KKKKKKKKKKKKK");
  //#else
  analogWrite(_PWM1,speed); // default to using analogWrite, mapping 255 to 255

  //#endif
  if (speed == 0)
  {
    digitalWrite(_INA1,LOW);   // Make the motor coast no
    digitalWrite(_INB1,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA1,LOW);
    digitalWrite(_INB1,HIGH);
  }
  else
  {
    //Serial.println("INA1-HIGH // INB1-LOW)");
    Serial.println(speed);
    digitalWrite(_INA1,HIGH);
    digitalWrite(_INB1,LOW);
  }
}

// Set speed for motor 2, speed is a number betwenn -255 and 255
void DualVNH2SP30::setM2Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 255)  // Max 
    speed = 255;
  //#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  //OCR1B = speed;
  //#else
  analogWrite(_PWM2,speed); // default to using analogWrite, mapping 255 to 255
  //#endif 
  if (speed == 0)
  {
    digitalWrite(_INA2,LOW);   // Make the motor coast no
    digitalWrite(_INB2,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA2,LOW);
    digitalWrite(_INB2,HIGH);
  }
  else
  {
    //Serial.println("INA2-HIGH // INB2-LOW)");
    digitalWrite(_INA2,HIGH);
    digitalWrite(_INB2,LOW);
  }
}

// Set speed for motor 1 and 2
void DualVNH2SP30::setSpeeds(int m1Speed, int m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}

// Brake motor 1, brake is a number between 0 and 255
void DualVNH2SP30::setM1Brake(int brake)
{
  //Serial.println("Breake M1");
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 255)  // Max brake
    brake = 255;
  digitalWrite(_INA1, LOW);
  digitalWrite(_INB1, LOW);
  //#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  //OCR1A = brake;
  //#else
  analogWrite(_PWM1,brake * 51 / 80); // default to using analogWrite, mapping 255 to 255
  //#endif
}

// Brake motor 2, brake is a number between 0 and 255
void DualVNH2SP30::setM2Brake(int brake)
{
  //Serial.println("Breake M2");
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 255)  // Max brake
    brake = 255;
  digitalWrite(_INA2, LOW);
  digitalWrite(_INB2, LOW);
  //#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  //OCR1B = brake;
  //#else
  analogWrite(_PWM2,brake * 51 / 80); // default to using analogWrite, mapping 255 to 255
  //#endif
}

// Brake motor 1 and 2, brake is a number between 0 and 255
void DualVNH2SP30::setBrakes(int m1Brake, int m2Brake)
{
  setM1Brake(m1Brake);
  setM2Brake(m2Brake);
}

// Return motor 1 current value in milliamps.
unsigned int DualVNH2SP30::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 130 mV per A = 37 mA per count
  return analogRead(_CS1) * 37;
}

// Return motor 2 current value in milliamps.
unsigned int DualVNH2SP30::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 130 mV per A = 37 mA per count
  return analogRead(_CS2) * 37;
}

// Return error status for motor 1 
unsigned char DualVNH2SP30::getM1Fault()
{
  //Serial.println("Fault M1");
  return !digitalRead(_EN1DIAG1);
}

// Return error status for motor 2 
unsigned char DualVNH2SP30::getM2Fault()
{
  //Serial.println("Fault M2");
  return !digitalRead(_EN2DIAG2);
}
