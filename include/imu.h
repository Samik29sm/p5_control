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

#endif