#ifndef CONTROL_H
#define CONTROL_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

#include "motor.h"
#include "joystick.h"
#include "flexsensor.h"
#include "imu.h"

extern float prevPitch; // Previous pitch value for IMU-based control
extern float prevAccel; // Previous acceleration value for IMU-based control


void flexsensorBasedControl(State *prevSate, State *currentState, bool verbose=false);
void accelBasedControl(State *prevSate, State *currentState, bool verbose=false);
void pitchBasedControl(State *prevSate, State *currentState, bool verbose=false);
void joystickBasedControl(State *prevSate, State *currentState, bool verbose=false);

#endif