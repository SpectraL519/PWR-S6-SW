#ifndef sw_lcd_display_hpp
#define sw_lcd_display_hpp

#include "LiquidCrystal_I2C.h"
#include <Arduino.h>

#define LCD_ADDR 0x27
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#define UPPER_LINE 0
#define LOWER_LINE 1
#define DEFAULT_POSITION 0

class sw_lcd_display_handler {
public:
    sw_lcd_display_handler() = default;
    ~sw_lcd_display_handler() = default;

    void setup() {
        Serial.println("LCD Display active!");
        this->_lcd.init();
        this->_lcd.backlight();
    }

    void print_str(const char* string, const uint8_t line = UPPER_LINE, const uint8_t pos = DEFAULT_POSITION) {
        this->_lcd.setCursor(pos, line);
        this->_lcd.print(string);
    }

    void clear_display() {
        this->_lcd.clear();
    }

private:
    LiquidCrystal_I2C _lcd{LCD_ADDR, LCD_WIDTH, LCD_HEIGHT};
};

#endif // sw_lcd_display_hpp
