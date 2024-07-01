#include "LiquidCrystal_I2C.h"
#include "Wheels.h"

byte LCDAddress = 0x27;
LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

const char* forwardCharacter = "F";
const char* backwardsCharacter = "B";
const char* stopCharacter = "S";
const uint8_t upperLine = 0;
const uint8_t lowerLine = 1;
const uint8_t leftPos = 0;
const uint8_t rightPos = 3;
// TODO: phisical display size: 2x16

// TODO: move to a led class
void printStr(const char* string, const uint8_t line, const uint8_t pos) {
  lcd.setCursor(pos, line);
  lcd.print(string);
}

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
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

  lcd.init();
  lcd.backlight();

  printStr(stopCharacter, lowerLine, leftPos);
  printStr(stopCharacter, lowerLine, rightPos);
}

void loop() {
  
  
  while(Serial.available()) {
    printStr("Dist: ", upperLine, 0);
    cmd = Serial.read();
    switch(cmd) {
      case 'w': {
        printStr(forwardCharacter, lowerLine, leftPos);
        printStr(forwardCharacter, lowerLine, rightPos);
        w.forward(); break;
      }
      case 'x': {
        printStr(backwardsCharacter, lowerLine, leftPos);
        printStr(backwardsCharacter, lowerLine, rightPos);
        w.back(); 
        break;
      }
      case 'a': {
        printStr(forwardCharacter, lowerLine, leftPos);
        w.forwardLeft(); 
        break;
      }
      case 'd': {
        printStr(forwardCharacter, lowerLine, rightPos);
        w.forwardRight(); 
        break;
      }
      case 'z': {
        printStr(backwardsCharacter, lowerLine, leftPos);
        w.backLeft(); 
        break;
      }
      case 'c': {
        printStr(backwardsCharacter, lowerLine, rightPos);
        w.backRight(); 
        break;
      }
      case 's': {
        printStr(stopCharacter, lowerLine, leftPos);
        printStr(stopCharacter, lowerLine, rightPos);
        w.stop(); 
        break;
      }
      case '1': {
        w.setSpeedLeft(75); 
        break;
      }
      case '2': {
        w.setSpeedLeft(200); 
        break;
      }
      case '9': {
        w.setSpeedRight(75); 
        break;
      }
      case '0': {
        w.setSpeedRight(200); 
        break;
      }
      case '5': {
        w.setSpeed(100); 
        break;
      }
      case 'q': {
        printStr(forwardCharacter, lowerLine, leftPos);
        printStr(forwardCharacter, lowerLine, rightPos);
        w.goForward(5);
        break;
      }
      case 'e': {
        printStr(backwardsCharacter, lowerLine, leftPos);
        printStr(backwardsCharacter, lowerLine, rightPos);
        w.goBack(5);
        break;
      }
    }
  }
}
