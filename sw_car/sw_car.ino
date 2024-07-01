#include "sw_wheels.hpp"
#include "sw_car_states.hpp"
#include "sw_ir_handler.hpp"
#include "sw_lcd_display_handler.hpp"
#include "sw_sonar.hpp"

sw_wheels wheels;
sw_car_state car_state;

sw_ir_handler ir_handler;
unsigned ir_command;
sw_lcd_display_handler lcd_handler;
sw_sonar sonar;

#define MIN_DIST_TO_STOP 40
#define MIN_DIST_TO_START 60

void setup() {
    Serial.begin(9600);
    Serial.println("------------------------");
    Serial.println("Auto driving enabled!");

    car_state = sw_car_state::idle;
    wheels.set_speed(DEFAULT_SPEED);

    ir_handler.setup();
    lcd_handler.setup();
    lcd_handler.print_str("S: IDLE");
    sonar.setup();
}

void loop() {
    if (ir_handler.try_decode()) {
        ir_handler.handle_receiver();
        ir_command = ir_handler.get_command();
        ir_handler.print_command(ir_command);
    }
    else {
        ir_command = IR_RECV_COMMAND_NONE;
    }

    if (ir_command == IR_RECV_COMMAND_HASH) {
        Serial.println("remote: stop!");
        car_state = sw_car_state::idle;
        wheels.stop();
        lcd_handler.clear_display();
        lcd_handler.print_str("S: IDLE");
        return;
    }

    switch (car_state) {
    case sw_car_state::idle: {
        car_state = sw_car_state::wfi_drive;
        Serial.println("wfi: drive");
        break;
    }
    case sw_car_state::driving: {
        const unsigned dist_to_obj = sonar.scan_forward();
        if (dist_to_obj < MIN_DIST_TO_STOP) {
            Serial.println("wfi: scan");
            car_state = sw_car_state::wfi_scan;
            wheels.stop();
            lcd_handler.clear_display();
            lcd_handler.print_str("S: wfi");
            lcd_handler.print_str("?: begin scan", LOWER_LINE);
        }
        break;
    }
    case sw_car_state::scanning: {
        const unsigned dist_to_obj = sonar.scan_surroundings();
        if (dist_to_obj > MIN_DIST_TO_START) {
            Serial.println("wfi: drive");
            car_state = sw_car_state::wfi_drive;
            wheels.stop();
            wheels.set_speed(DEFAULT_SPEED);
            lcd_handler.clear_display();
            lcd_handler.print_str("S: wfi");
            lcd_handler.print_str("!: path found", LOWER_LINE);
        }
        break;
    }
    case sw_car_state::wfi_scan: {
        if (ir_command == IR_RECV_COMMAND_OK) {
            Serial.println("scanning");
            car_state = sw_car_state::scanning;
            wheels.turn_right();
            lcd_handler.clear_display();
            lcd_handler.print_str("S: scanning");
        }
        break;
    }
    case sw_car_state::wfi_drive: {
        if (ir_command == IR_RECV_COMMAND_OK) {
            Serial.println("driving");
            car_state = sw_car_state::driving;
            wheels.drive_forward();
            lcd_handler.clear_display();
            lcd_handler.print_str("S: driving");
        }
        break;
    }
    }
}
