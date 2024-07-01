#include <IRremote.hpp>
#define IR_RECEIVE_PIN 7

#define IR_RECV_COMMAND_0 25
#define IR_RECV_COMMAND_1 69
#define IR_RECV_COMMAND_2 70
#define IR_RECV_COMMAND_3 71
#define IR_RECV_COMMAND_4 68
#define IR_RECV_COMMAND_5 64
#define IR_RECV_COMMAND_6 67
#define IR_RECV_COMMAND_7 7
#define IR_RECV_COMMAND_8 21
#define IR_RECV_COMMAND_9 9
#define IR_RECV_COMMAND_ASTERIX 22
#define IR_RECV_COMMAND_HASH 13
#define IR_RECV_COMMAND_OK 28
#define IR_RECV_COMMAND_ARROW_UP 24
#define IR_RECV_COMMAND_ARROW_DOWN 82
#define IR_RECV_COMMAND_ARROW_LEFT 8
#define IR_RECV_COMMAND_ARROW_RIGHT 90

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

void handleReceiver() {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println("Received noise or an unknown (or not yet enabled) protocol");
        
        IrReceiver.printIRResultRawFormatted(&Serial, true);
        IrReceiver.resume();
        return;
    } 

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    IrReceiver.resume();
}

void printCommand(const unsigned command) {
    Serial.print("[Receiver] Command = ");
    Serial.println(command);
}

void setup() {
    w.attach(IN4, IN3, ENB, IN1, IN2, ENA);

    Serial.begin(9600);
    Serial.println("Forward: WAD");
    Serial.println("Back: ZXC");
    Serial.println("Stop: S");
    Serial.println("Forward [5]: Q");
    Serial.println("Back [5]: E");

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
    Serial.print("Ready to receive IR signals of protocols: ");
    printActiveIRProtocols(&Serial);
    Serial.print("at pin ");
    Serial.println(IR_RECEIVE_PIN);
}

void loop() {
    if (!IrReceiver.decode()) {
        return;
    }

    handleReceiver();
    printCommand(IrReceiver.decodedIRData.command);
    switch (IrReceiver.decodedIRData.command) {
    case IR_RECV_COMMAND_0: {
        w.setSpeed(0);
        break;
    }
    case IR_RECV_COMMAND_1: {
        w.setSpeed(100);
        break;
    }
    case IR_RECV_COMMAND_2: {
        w.setSpeed(150);
        break;
    }
    case IR_RECV_COMMAND_3: {
        w.setSpeed(200);
        break;
    }
    case IR_RECV_COMMAND_4: {
        w.setSpeed(250);
        break;
    }
    case IR_RECV_COMMAND_ARROW_UP: {
        w.forward();
        break;
    }
    case IR_RECV_COMMAND_ARROW_DOWN: {
        w.back();
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
