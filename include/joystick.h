#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupJOYSTICK();
void readJOYSTICK_Y(int *y, bool verbose=false);
void joystickBasedStateChange(State *prevState, State *currentState, bool verbose=false);

#endif