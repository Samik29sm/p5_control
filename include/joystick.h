#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupJOYSTICK();
void readJOYSTICK(int *x, int *y, int *sw, bool verbose=false);
void processJOYSTICK(int x, int sw, bool *prevSwitchState, bool *controlMode, ControlMode control, State *prevState, State *currentState, bool verbose=false);

#endif