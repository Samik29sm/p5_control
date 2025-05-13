#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupMOTOR();
void motorUP(bool verbose=false);
void motorDOWN(bool verbose=false);
void motorREST(bool verbose=false);
void stateBasedMovement(State currentState);

#endif