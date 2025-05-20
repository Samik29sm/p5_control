#ifndef CONSTANTS_H
#define CONSTANTS_H

// Arm States
enum State { REST, UP, DOWN };

// Control Modes
enum ControlMode { JOYSTICK, FLEXSENSOR, IMU_accel, IMU_pitch };

//  Motor constant speed (max PWM = 255)
const int CONSTANT_SPEED = 255;
const int RAMP_DELAY = 20;   // time btw PWM step
const int STEP_SIZE = 5;     // PWM step size


// Joystick
#define JOYSTICK_REST_POSITION 532
#define JOYSTICK_DOWN_THRESHOLD 450
#define JOYSTICK_UP_THRESHOLD 800

// IMU
#define IMU_ACCEL_THRESHOLD_CHANGE_HIGH 0.5
#define IMU_ACCEL_THRESHOLD_CHANGE_LOW -0.5
#define IMU_ACCEL_THRESHOLD_REST_HIGH 0.1
#define IMU_ACCEL_THRESHOLD_REST_LOW -0.1
#define IMU_PITCH_THRESHOLD_MOVE 10
#define IMU_PITCH_THRESHOLD_REST 5

// FLEXSENSOR 
#define FLEXSENSOR_THRESHOLD_UP -400.0
#define FLEXSENSOR_THRESHOLD_DOWN -150.0

#endif