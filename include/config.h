#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// BRANCHEMENT SUR L'ARDUINO
// Joystick: A0
// Switch: A2
// Flexsensor: A3
// Motor: D8
// IMU: I2C


// Motor configuration - Pins for MD13S
const int PWM_PIN = 9;   // Motor speed via PWM
const int DIR_PIN = 8;   // Motor direction

// Joystick configuration - B103 348
const int Y_PIN = 1; // analog pin connected to X output

// Switch configuration 
const int SW_PIN = 2; // analog pin connected to switch output

// RGB LED configuration
const int RED_PIN = 3;   // Red LED pin
const int GREEN_PIN = 5; // Green LED pin
const int BLUE_PIN = 6;  // Blue LED pin

// Battery reader configuration
const int BATTERY_PIN = A3; // Analog pin for battery voltage

// Flexsensor configuration
const int FLEXSENSOR_PIN = A4;
const int FLEXSENSOR_VCC = 5;
const float FLEXSENSOR_RDIV = 47000.0;
const float FLEXSENSOR_FLATR = 25000.0; // Resistance when flat
const float FLEXSENSOR_BENDR = 10000.0; // Resistance at 90 deg

#endif