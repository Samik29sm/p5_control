#ifndef FLEXSENSOR_H
#define FLEXSENSOR_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupFLEXSENSOR();
void readFLEXSENSOR(float *angle, bool verbose=false);
void flexsensorBasedStateChange(State *prevState, State *currentState, bool verbose=false);

#endif