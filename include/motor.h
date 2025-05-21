#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupMOTOR();
void motorUP(bool verbose=false);
void motorDOWN(bool verbose=false);
void motorREST(bool verbose=false);
void rampPWM(int startPWM, int endPWM, int step_size, bool direction, bool verbose=false);
void rampPWMUP(int startPWM, int endPWM, bool direction, bool verbose=false);
void rampPWMDOWN(int startPWM, int endPWM, bool direction, bool verbose=false);
void stateBasedMovement(State *prevState, State *currentState, bool verbose=false);

#endif