/*
 * In1 = 1, In2 = 0 -> Out1 = +, Out2 = -
 * In1 = 0, In2 = 1 -> Out1 = -, Out2 = +
 * EnA -> enables electricity flow
 */

#define ENA 11
#define ENB 10
#define IN1 5
#define IN2 4
#define IN3 3
#define IN4 2

void enablePin(const unsigned pin) {
  digitalWrite(pin, HIGH);
}

void disablePin(const unsigned pin) {
  digitalWrite(pin, LOW);
}

void leftWheelBackwards() {
  enablePin(IN1);
  disablePin(IN2);
}

void rightWheelBackwards() {
  enablePin(IN4);
  disablePin(IN3);
}

void driveBackwards() {
  leftWheelBackwards();
  rightWheelBackwards();
}

void leftWheelForward() {
  disablePin(IN1);
  enablePin(IN2);
}

void rightWheelForward() {
  disablePin(IN4);
  enablePin(IN3);
}

void driveForward() {
  leftWheelForward();
  rightWheelForward();
}

void stopLeftWheel() {
  disablePin(IN1);
  disablePin(IN2);
}

void stopRightWheel() {
  disablePin(IN3);
  disablePin(IN4);
}

void stopWheels() {
  stopLeftWheel();
  stopRightWheel();
}

void setup() {}

void loop() {
  for (unsigned speedIndicator = 50; speedIndicator <= 250; speedIndicator += 50) {
    analogWrite(ENA, speedIndicator);
    analogWrite(ENB, speedIndicator);
    driveForward();
    delay(1000);
    stopWheels();
    delay(1000);
  }
}
