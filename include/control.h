#ifndef CONTROL_H
#define CONTROL_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

#include "motor.h"
#include "joystick.h"
#include "flexsensor.h"


typedef void (*ControlFunc)(State *prev, State *curr, bool verbose);

// Function table indexed by ControlMode enum
extern ControlFunc controlTable[]; 

// Function to get the control function based on the ControlMode    
ControlFunc getControlFunction(ControlMode mode);

void controlMotor(ControlFunc BasedStateChangeFCT, State *prevState, State *currentState, bool verbose=false);

#endif