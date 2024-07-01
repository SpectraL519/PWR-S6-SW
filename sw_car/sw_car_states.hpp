#ifndef sw_car_state_hpp
#define sw_car_state_hpp

enum class sw_car_state {
    idle,
    driving,
    scanning,
    wfi_drive, // waiting for input -> begin scanning
    wfi_scan   // waiting for input -> drive
};

// ! redunant
enum class sw_car_direction {
    none, forward, back, left, right
};

#endif // sw_car_state_hpp
