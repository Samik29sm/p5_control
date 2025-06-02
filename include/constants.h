#ifndef CONSTANTS_H
#define CONSTANTS_H

// Arm States
enum State { REST, UP, DOWN };

// Control Modes
enum ControlMode { JOYSTICK, FLEXSENSOR};

// Color LED
enum Color { RED, GREEN, BLUE, OFF };

//  Motor constant speed (max PWM = 255)
const int CONSTANT_SPEED = 255;
const int RAMP_DELAY = 20;   // time btw PWM step
const int STEP_SIZE_DOWN = 5;      // PWM step size when going down 
const int STEP_SIZE_UP = 3;     // PWM step size when going up

// Battery threshold
// max tension: 4.536
// medium tension: 3.88
// min tension: 3.672
const float BATTERY_THRESHOLD_MEDIUM = 3.88;
const float BATTERY_THRESHOLD_EMPTY = 3.672;

const int LED_DISPLAY = 1;



// Joystick
#define JOYSTICK_REST_POSITION 532
#define JOYSTICK_DOWN_THRESHOLD 450
#define JOYSTICK_UP_THRESHOLD 800


// FLEXSENSOR 
#define FLEXSENSOR_THRESHOLD_UP -300.0
#define FLEXSENSOR_THRESHOLD_DOWN -150.0

#endif