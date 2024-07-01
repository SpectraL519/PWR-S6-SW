// Wheels utility
#include "Wheels.h"

// left wheel
#define ENA 6
#define IN1 7
#define IN2 4

// right wheel
#define ENB 5
#define IN3 3
#define IN4 2

Wheels w;
unsigned currentSpeed = 0;
const unsigned defaultSpeed = 100;
const unsigned turnSpeedDelta = 15;

void setWheelsSpeed(const unsigned speed) {
    currentSpeed = speed;
    w.setSpeed(currentSpeed);
}

#include "ir_remote_utility.h"

// LCD display utility
/*
#include "LiquidCrystal_I2C.h"

byte LCDAddress = 0x27;
LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

const char* forwardCharacter = "F";
const char* backwardsCharacter = "B";
const char* stopCharacter = "S";
const uint8_t upperLine = 0;
const uint8_t lowerLine = 1;
const uint8_t leftPos = 0;
const uint8_t rightPos = 3;

void printStr(const char* string, const uint8_t line, const uint8_t pos) {
    lcd.setCursor(pos, line);
    lcd.print(string);
}
*/

// Servo utility
// /*
#include <Servo.h>

// servo sonar pins (HC-SR04)
#define TRIG A4
#define ECHO A5

// servo control pin (must be PWM)
#define SERVO 3
#define FORWARD_ANGLE 90

Servo servo;
byte current_angle;

void lookAndTellDistance(byte angle) {
    unsigned long tot; // (time-of-travel)
    unsigned int distance;

    Serial.print("Looking at an angle: ");
    Serial.print(angle);
    servo.write(angle);

    // launch sonar (10 ms pulse on `TRIGGER`)
    digitalWrite(TRIG, HIGH);
    delay(10);
    digitalWrite(TRIG, LOW);
    tot = pulseIn(ECHO, HIGH);

    // speed of sound = 340m/s => 1 cm in 29 microseconds
    // distance in both ways:
    distance = tot / 58;

    Serial.print(": object detected in distance ");
    Serial.println(distance);
}
// */

void setup() {
    w.attach(IN4, IN3, ENB, IN1, IN2, ENA);

    Serial.begin(9600);
    Serial.println("------------");
    Serial.println("Remote steering");

    irSetup();

    // Servo setup
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    servo.attach(SERVO);
    for (byte angle = 0; angle <= 180; angle+= 20) {
        lookAndTellDistance(angle);
        delay(500);
    }

    current_angle = FORWARD_ANGLE;
    servo.write(current_angle);
}

volatile char cmd;

void loop() {
    if (!IrReceiver.decode())
        return;

    irHandleReceiver();
    const auto irCommand = IrReceiver.decodedIRData.command;
    irPrintCommand(irCommand);
    switch(irCommand) {
    case IR_RECV_COMMAND_0: {
        setWheelsSpeed(0);
        break;
    }
    case IR_RECV_COMMAND_1: {
        setWheelsSpeed(100);
        break;
    }
    case IR_RECV_COMMAND_2: {
        setWheelsSpeed(150);
        break;
    }
    case IR_RECV_COMMAND_3: {
        setWheelsSpeed(200);
        break;
    }
    case IR_RECV_COMMAND_4: {
        setWheelsSpeed(250);
        break;
    }
    case IR_RECV_COMMAND_ARROW_UP: {
        if (currentSpeed == 0)
            setWheelsSpeed(defaultSpeed);
        w.forward();
        break;
    }
    case IR_RECV_COMMAND_ARROW_DOWN: {
        if (currentSpeed == 0)
            setWheelsSpeed(defaultSpeed);
        w.back();
        break;
    }
    case IR_RECV_COMMAND_ARROW_RIGHT: {
        if (currentSpeed == 0)
            setWheelsSpeed(defaultSpeed);
        w.setSpeedRight(currentSpeed - turnSpeedDelta);
        w.forwardLeft();
        w.backRight();
        break;
    }
    case IR_RECV_COMMAND_ARROW_LEFT: {
        if (currentSpeed == 0)
            setWheelsSpeed(defaultSpeed);
        w.setSpeedLeft(currentSpeed - turnSpeedDelta);
        w.forwardRight();
        w.backLeft();
        break;
    }
    case IR_RECV_COMMAND_OK: {
        w.stop();
        break;
    }
    default: {
        Serial.println("[Receiver] Unsupported command");
    }
    }
}
