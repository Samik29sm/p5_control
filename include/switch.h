#ifndef SWITCH_H
#define SWITCH_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupSWITCH();
void readSWITCH(int *sw, bool verbose=false);
void processSWITCH(int sw, ControlMode *controlMode, ControlMode control, bool verbose=false);

#endif