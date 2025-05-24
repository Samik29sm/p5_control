#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>

#include "led.h"

#include "constants.h"
#include "config.h"

void setupBATTERY();
void readBATTERY(float *voltage, bool verbose=false);
void controlLED(float *voltage, bool verbose=false);


#endif