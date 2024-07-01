#include "Wheels.h"

// left wheel
#define ENA 11
#define IN1 5
#define IN2 4

// right wheel
#define ENB 10
#define IN3 3
#define IN4 2

Wheels w;
volatile char cmd;

void setup() {
  w.attach(IN3, IN4, ENB, IN2, IN1, ENA);
  // w.attach(7, 4, 5, 8, 12, 6);
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': w.forward(); break;
      case 'x': w.back(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
    }
  }
}
