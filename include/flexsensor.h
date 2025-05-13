#ifndef FLEXSENSOR_H
#define FLEXSENSOR_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupFLEXSENSOR();
void readFLEXSENSOR(float *angle, bool verbose=false);
void flexsensorBasedStateChange(float angle, State *currentState, bool *stateChanged, bool verbose=false);

#endif