#include "sw_wheels.hpp"

#include <Arduino.h>

// left wheel
#define PIN_LE 6
#define PIN_LF 7
#define PIN_LB 4

// right wheel
#define PIN_RE 5
#define PIN_RB 3
#define PIN_RF 2

#define FPIN_IDX 0
#define BPIN_IDX 1
#define EPIN_IDX 2

#define SET_MOVEMENT(motor_pins, forward_pin_signal, back_pin_signal) \
    digitalWrite(motor_pins[FPIN_IDX], forward_pin_signal);           \
    digitalWrite(motor_pins[BPIN_IDX], back_pin_signal)

#define TIME_FOR_DIST 25

sw_wheels::sw_wheels() {
    this->_attach_pins_left();
    this->_attach_pins_right();
}

void sw_wheels::set_speed(const unsigned speed) {
    this->_set_speed_left(speed);
    this->_set_speed_right(speed);
    this->_current_speed = speed;
}

void sw_wheels::validate_speed() {
    if (this->_current_speed == NO_SPEED)
        this->_current_speed = DEFAULT_SPEED;
    this->set_speed(this->_current_speed);
}

unsigned sw_wheels::current_speed() const {
    return this->_current_speed;
}

void sw_wheels::stop() {
    this->_left_stop();
    this->_right_stop();
}

void sw_wheels::drive_forward() {
    this->validate_speed();
    this->_left_forward();
    this->_right_forward();
}

void sw_wheels::drive_backwards() {
    this->validate_speed();
    this->_left_backwards();
    this->_right_backwards();
}

void sw_wheels::turn_left() {
    this->_set_speed_right(MIN_SPPED + TURN_SPEED_DELTA);
    this->_set_speed_left(MIN_SPPED);
    this->_right_forward();
    this->_left_backwards();
}

void sw_wheels::turn_right() {
    this->_set_speed_left(MIN_SPPED + TURN_SPEED_DELTA);
    this->_set_speed_right(MIN_SPPED);
    this->_left_forward();
    this->_right_backwards();
}

void sw_wheels::_attach_pins_left() {
    pinMode(PIN_LF, OUTPUT);
    pinMode(PIN_LB, OUTPUT);
    pinMode(PIN_LE, OUTPUT);
    this->_pins_left[FPIN_IDX] = PIN_LF;
    this->_pins_left[BPIN_IDX] = PIN_LB;
    this->_pins_left[EPIN_IDX] = PIN_LE;
}

void sw_wheels::_attach_pins_right() {
    pinMode(PIN_RF, OUTPUT);
    pinMode(PIN_RB, OUTPUT);
    pinMode(PIN_RE, OUTPUT);
    this->_pins_right[FPIN_IDX] = PIN_RF;
    this->_pins_right[BPIN_IDX] = PIN_RB;
    this->_pins_right[EPIN_IDX] = PIN_RE;
}

void sw_wheels::_set_speed_left(const unsigned speed) {
    analogWrite(this->_pins_left[EPIN_IDX], speed);
}

void sw_wheels::_set_speed_right(const unsigned speed) {
    analogWrite(this->_pins_right[EPIN_IDX], speed);
}

void sw_wheels::_left_stop() {
    SET_MOVEMENT(this->_pins_left, LOW, LOW);
}

void sw_wheels::_right_stop() {
    SET_MOVEMENT(this->_pins_right, LOW, LOW);
}

void sw_wheels::_left_forward() {
    SET_MOVEMENT(this->_pins_left, HIGH, LOW);
}

void sw_wheels::_right_forward() {
    SET_MOVEMENT(this->_pins_right, HIGH, LOW);
}

void sw_wheels::_left_backwards() {
    SET_MOVEMENT(this->_pins_left, LOW, HIGH);
}

void sw_wheels::_right_backwards() {
    SET_MOVEMENT(this->_pins_right, LOW, HIGH);
}
