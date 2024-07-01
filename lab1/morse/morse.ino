#define LED 13

#include <stdbool.h>

volatile char serialInput;

const unsigned shortSignalTime = 75;
const unsigned longSignalTime = 3 * shortSignalTime;
const unsigned signalBreakTime = shortSignalTime;
const unsigned characterBreakTime = 3 * shortSignalTime;
const unsigned wordBreakTime = 7 * shortSignalTime;

void blink(const unsigned blinkTime = shortSignalTime, const unsigned breakTime = signalBreakTime) {
    digitalWrite(LED, HIGH);
    delay(blinkTime);
    digitalWrite(LED, LOW);
    delay(breakTime);
}

void noSignal(const unsigned breakTime) {
    delay(breakTime);
}

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    while(Serial.available()) {
        serialInput = Serial.read();
        switch(serialInput) {
        case 'k' : { // — • —
            blink(longSignalTime);
            blink();
            blink(longSignalTime, characterBreakTime);
            break;
        }
        case 'u' : { // • • —
            blink();
            blink();
            blink(longSignalTime, characterBreakTime);
            break;
        }
        case 'b': { // — • • •
            blink(longSignalTime);
            blink();
            blink();
            blink(shortSignalTime, characterBreakTime);
            break;
        }
        case 'a': { // • —
            blink();
            blink(longSignalTime, characterBreakTime);
            break;
        }
        case 's': { // • • •
            blink();
            blink();
            blink(shortSignalTime, characterBreakTime);
            break;
        }
        case 'o': { // — — —
            blink(longSignalTime);
            blink(longSignalTime);
            blink(longSignalTime, characterBreakTime);
            break;
        }
        case '2': { // • • — — —
            blink();
            blink();
            blink(longSignalTime);
            blink(longSignalTime);
            blink(longSignalTime, characterBreakTime);
            break;
        }
        case ' ': { // . x7
            noSignal(wordBreakTime);
            break;
        }
        default: 
            Serial.println("?");
        }
    }
    Serial.println(".");
}
