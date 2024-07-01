// https://playground.arduino.cc/code/timer1
// Jeśli nie masz tej biblioteki, wybierz:
// Narzędzia->Zarządzaj bibliotekami, w oknie wyszukaj
// bibliotekę TimerOne i zanistaluj.
//

#include "Wheels.h"
#include "LiquidCrystal_I2C.h"
#include "TimerOne.h"

#include <stdbool.h>

// left wheel
#define ENA 11
#define IN1 5
#define IN2 4

// right wheel
#define ENB 10
#define IN3 3
#define IN4 2

// wheel speed data
const int defaultSpeed = 150;
const int speedDelta = 50;
int speed = defaultSpeed;

Wheels w;
volatile char cmd;

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

// pin, na którym obserwujemy działanie
// pin 13 to dioda LED, ale możesz podłączyć też głośnik
#define BEEPER 13

// bip period data
const long int defaultBeepPeriod = 500000;
const long int beepPeriodDelta = 200000;
long int beepPeriod = defaultBeepPeriod;

// aktualizuje Timer1 aktualną wartością beepPeriod
void updateBeepInterrupt(const bool stop = false) {
    Timer1.detachInterrupt();
    if (stop)
        Timer1.attachInterrupt(stopBeep);
    else
        Timer1.attachInterrupt(doBeep, beepPeriod);
}

void doBeep() {
    digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
}

void stopBeep() {
    digitalWrite(BEEPER, 0);
}

void setup() {
    w.attach(IN3, IN4, ENB, IN2, IN1, ENA);

    pinMode(BEEPER, OUTPUT);
    Timer1.initialize();

    Serial.begin(9600);
    Serial.println("Forward: W");
    Serial.println("Back: X");
    Serial.println("Stop: S");

    lcd.init();
    lcd.backlight();

    printStr(stopCharacter, lowerLine, leftPos);
    printStr(stopCharacter, lowerLine, rightPos);
}

bool goingBackwards = false;
void loop() {
    while(Serial.available()) {
        printStr("Dist: ", upperLine, 0);
        cmd = Serial.read();
        switch(cmd) {
        case 'w': {
            printStr(forwardCharacter, lowerLine, leftPos);
            printStr(forwardCharacter, lowerLine, rightPos);
            goingBackwards = false;
            updateBeepInterrupt(!goingBackwards);
            w.forward();
            break;
        }
        case 'x': {
            printStr(backwardsCharacter, lowerLine, leftPos);
            printStr(backwardsCharacter, lowerLine, rightPos);
            goingBackwards = true;
            w.back();
            updateBeepInterrupt(!goingBackwards);
            break;
        }
        case 's': {
            printStr(stopCharacter, lowerLine, leftPos);
            printStr(stopCharacter, lowerLine, rightPos);
            goingBackwards = false;
            w.stop();
            updateBeepInterrupt(!goingBackwards);
            break;
        }
        case '5': {
            speed = defaultSpeed;
            w.setSpeed(speed);
            beepPeriod = defaultBeepPeriod;
            updateBeepInterrupt(!goingBackwards);
            break;
        }
        case '+': {
            speed += speedDelta;
            w.setSpeed(speed);
            beepPeriod -= beepPeriodDelta;
            updateBeepInterrupt(!goingBackwards);
            break;
        }
        case '-': {
            speed -= speedDelta;
            w.setSpeed(speed);
            beepPeriod += beepPeriodDelta;
            updateBeepInterrupt(!goingBackwards);
            break;
        }
        // case 'q': {
        //     printStr(forwardCharacter, lowerLine, leftPos);
        //     printStr(forwardCharacter, lowerLine, rightPos);
        //     w.goForward(5);
        //     break;
        // }
        // case 'e': {
        //     printStr(backwardsCharacter, lowerLine, leftPos);
        //     printStr(backwardsCharacter, lowerLine, rightPos);
        //     w.goBack(5);
        //     break;
        // }
        }
    }
}
