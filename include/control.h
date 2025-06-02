#ifndef CONTROL_H
#define CONTROL_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

#include "motor.h"
#include "joystick.h"
#include "flexsensor.h"


void flexsensorBasedControl(State *prevState, State *currentState, bool verbose=false);
void joystickBasedControl(State *prevState, State *currentState, bool verbose=false);

#endif