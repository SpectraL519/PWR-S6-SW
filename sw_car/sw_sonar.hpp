#ifndef sw_sonar_hpp
#define sw_sonar_hpp

#include <Servo.h>

#define TRIG A3
#define ECHO A2
#define SERVO 9

#define FORWARD_ANGLE 90
#define LEFT_ANGLE 110
#define RIGHT_ANGLE 70

class sw_sonar {
public:
    sw_sonar() = default;
    ~sw_sonar() = default;

    void setup();

    unsigned scan_forward();
    unsigned scan_surroundings(); // ! redunant

private:
    void _set_angle(const unsigned angle);
    unsigned _measure_distance(const unsigned angle);

    Servo _servo;
    unsigned _current_angle = FORWARD_ANGLE;
};

#endif // sw_sonar_hpp
