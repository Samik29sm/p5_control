#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupJOYSTICK();
void readJOYSTICK_X(int *x, bool verbose=false);
void joystickBasedStateChange(int x, State *prevState, State *currentState, bool verbose=false);

#endif