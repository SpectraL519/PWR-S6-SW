#ifndef sw_ir_handler_hpp
#define sw_ir_handler_hpp

#include <IRremote.hpp>

#define IR_RECEIVE_PIN 8

#define IR_RECV_COMMAND_NONE -1
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

class sw_ir_handler {
public:
    sw_ir_handler() = default;
    ~sw_ir_handler() = default;

    void setup() const {
        IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
        Serial.print("Ready to receive IR signals of protocols: ");
        printActiveIRProtocols(&Serial);
        Serial.print("at pin ");
        Serial.println(IR_RECEIVE_PIN);
    }

    bool try_decode() const {
        if (!IrReceiver.decode()) {
            // Serial.println("Cannot decode IR data");
            return false;
        }

        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println("Received noise or an unknown (or not yet enabled) protocol");

            IrReceiver.printIRResultRawFormatted(&Serial, true);
            IrReceiver.resume();
            return false;
        }

        return true;
    }

    void handle_receiver() const {
        Serial.println();
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        IrReceiver.resume();
    }

    unsigned get_command() const {
        return IrReceiver.decodedIRData.command;
    }

    void print_command(const unsigned command) const {
        Serial.print("[Receiver] Command = ");
        Serial.println(command);
    }
};

#endif // sw_ir_handler_hpp
