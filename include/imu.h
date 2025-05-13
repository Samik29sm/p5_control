#ifndef IMU_H
#define IMU_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

#include <Adafruit_BNO055.h>

// Declare the BNO055 object as an external variable
extern Adafruit_BNO055 bno;

void setupIMU();
bool calibration(bool gyroBasedCalibration, bool accelBasedCalibration, bool magBasedCalibration, bool verbose=false);
float readAccel();
float readPitch();
void accelBasedStateChange (float accZ, State *currentState, bool *stateChanged, bool verbose=false);
void pitchBasedStateChange(float rawPitch, float prevPitch, State *currentState, bool *stateChanged, bool verbose=false);


#endif