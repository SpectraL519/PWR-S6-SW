#ifndef sw_wheels_hpp
#define sw_wheels_hpp

#define NO_SPEED 0
#define MIN_SPPED 100
#define DEFAULT_SPEED 150
#define TURN_SPEED_DELTA 15

#define NO_PINS_PER_MOTOR 3

class sw_wheels {
public:
    sw_wheels();
    ~sw_wheels() = default;

    void set_speed(const unsigned speed);
    void validate_speed();
    unsigned current_speed() const;

    void stop();
    void drive_forward();
    void drive_backwards();
    void turn_left();
    void turn_right();

private:
    void _attach_pins_left();
    void _attach_pins_right();

    void _set_speed_right(const unsigned speed);
    void _set_speed_left(const unsigned speed);

    void _left_stop();
    void _right_stop();
    void _left_forward();
    void _right_forward();
    void _left_backwards();
    void _right_backwards();

    int _pins_left[NO_PINS_PER_MOTOR];
    int _pins_right[NO_PINS_PER_MOTOR];

    unsigned _current_speed = NO_SPEED;
};

#endif // sw_wheels_hpp
