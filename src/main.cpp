#include <Arduino.h>
#include <Wire.h>

#include "constants.h"
#include "config.h"
#include "motor.h"
#include "constants.h"
#include "joystick.h"
#include "motor.h"
#include "imu.h"
#include "flexsensor.h"


// State Variables
bool controlMode = false;
State currentState = REST;
State prevState = REST;
bool prevSwitchState = HIGH;

// Control Mode: flexsensor or IMU, joystick if switch is pressed
ControlMode control = FLEXSENSOR;
// ControlMode control = IMU;

const bool verbose = true;

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_SPEED);

  setupMOTOR();
  setupJOYSTICK();
  if (control == FLEXSENSOR) {
    setupFLEXSENSOR();
  } else if (control == IMU) {
    setupIMU();
  }
}

void loop() {
  // Read joystick values 
  int x, y, sw;
  readJOYSTICK(&x, &y, &sw, verbose);
  processJOYSTICK(x, sw, &prevSwitchState, &controlMode, control, &prevState, &currentState, verbose);
  delay(200);
}

