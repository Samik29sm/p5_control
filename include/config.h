#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Motor configuration - Pins for MD13S
const int PWM_PIN = 9;   // Motor speed via PWM
const int DIR_PIN = 8;   // Motor direction

// Joystick configuration - B103 348
const int X_PIN = 1; // analog pin connected to X output
const int SW_PIN = 0; // analog pin connected to switch output

// Flexsensor configuration
const int FLEXSENSOR_PIN = A0;
const int FLEXSENSOR_VCC = 5;
const float FLEXSENSOR_RDIV = 47000.0;
const float FLEXSENSOR_FLATR = 10000.0; // Resistance at 90 deg
const float FLEXSENSOR_BENDR = 10000.0; // Resistance when flat 

#endif