#include <IRremote.hpp>
#define IR_RECEIVE_PIN 8

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

void irSetup() {
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
    Serial.print("Ready to receive IR signals of protocols: ");
    printActiveIRProtocols(&Serial);
    Serial.print("at pin ");
    Serial.println(IR_RECEIVE_PIN);
}

void irHandleReceiver() {
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

void irPrintCommand(const unsigned command) {
    Serial.print("[Receiver] Command = ");
    Serial.println(command);
}
