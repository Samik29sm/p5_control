#include <Arduino.h>
#include <Wire.h>

#include "constants.h"
#include "config.h"
#include "control.h"
#include "motor.h"
#include "constants.h"
#include "joystick.h"
#include "motor.h"
#include "imu.h"
#include "flexsensor.h"

const bool verbose = true;

// State Variables
State currentState = REST;
State prevState = REST;

// Control Mode: flexsensor or IMU based on acceleration or pitch, joystick if switch is pressed
// ControlMode control = JOYSTICK; 
ControlMode control = FLEXSENSOR;
// ControlMode control = IMU_accel;
// ControlMode control = IMU_pitch;

ControlMode controlMode = control;

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_SPEED);

  setupMOTOR();
  setupJOYSTICK();
  if (control == FLEXSENSOR) {
    setupFLEXSENSOR();
  } else if (control == IMU_accel or control == IMU_pitch) {
    setupIMU();
  }
}

void loop() {
  // Read joystick value of the switch
  int sw;
  readJOYSTICK_SW(&sw, verbose);
  Serial.print("control before: ");
  Serial.println(controlMode);
  processJOYSTICK(sw, &controlMode, control, verbose);
  Serial.print("control after: ");
  Serial.println(controlMode);

  // Control based on the selected mode
  switch(controlMode) {
    case FLEXSENSOR: flexsensorBasedControl(&prevState, &currentState, verbose); break;
    case IMU_accel: accelBasedControl(&prevState, &currentState, verbose); break;
    case IMU_pitch: pitchBasedControl(&prevState, &currentState, verbose); break; 
    case JOYSTICK: joystickBasedControl(&prevState, &currentState, verbose); break;
  }
  delay(100);
}
