#include "sw_sonar.hpp"

#include <Arduino.h>

void sw_sonar::setup() {
    this->_servo.attach(SERVO);
    this->_set_angle(LEFT_ANGLE);
    delay(20);
    this->_set_angle(RIGHT_ANGLE);
    delay(20);
    this->_set_angle(FORWARD_ANGLE);
}

unsigned sw_sonar::scan_forward() {
    return this->_measure_distance(FORWARD_ANGLE);
}

unsigned sw_sonar::scan_surroundings() {
    const unsigned distance_left = this->_measure_distance(LEFT_ANGLE);
    // delay(10);
    const unsigned distance_right = this->_measure_distance(RIGHT_ANGLE);
    // delay(10);
    const unsigned side_distance = distance_left > distance_right ? distance_left : distance_right;
    const unsigned forward_distance = this->_measure_distance(FORWARD_ANGLE);

    return side_distance > forward_distance ? side_distance : forward_distance;
}

void sw_sonar::_set_angle(const unsigned angle) {
    this->_current_angle = angle;
    this->_servo.write(this->_current_angle);
}

unsigned sw_sonar::_measure_distance(const unsigned angle) {
    this->_set_angle(angle);

    Serial.print("Measuring distance at an angle: ");
    Serial.println(this->_current_angle);

    // launch sonar (10 ms pulse on `TRIGGER`)
    digitalWrite(TRIG, HIGH);
    delay(10);
    digitalWrite(TRIG, LOW);
    unsigned long time_of_travel = pulseIn(ECHO, HIGH);

    // speed of sound = 340m/s => 1 cm in 29 microseconds
    // distance in both ways:
    unsigned distance = time_of_travel / 58;

    Serial.print("Object detected at distance: ");
    Serial.println(distance);

    return distance;
}
