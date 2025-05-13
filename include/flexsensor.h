#ifndef FLEXSENSOR_H
#define FLEXSENSOR_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupFLEXSENSOR();
void readFLEXSENSOR(int *value, bool verbose=false);

#endif