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
#include "switch.h"
#include "led.h"
#include "battery.h"

const bool verbose = true;

// State Variables
State currentState = REST;
State prevState = REST;

// Control Mode: flexsensor or IMU based on acceleration or pitch, joystick if switch is pressed
ControlMode control = JOYSTICK; 
// ControlMode control = FLEXSENSOR;
// ControlMode control = IMU_accel;
// ControlMode control = IMU_pitch;

ControlMode controlMode = control;

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_SPEED);

  setupMOTOR();
  setupSWITCH();
  setupJOYSTICK();
  setupLED();
  setupBATTERY();
  if (control == FLEXSENSOR) {
    setupFLEXSENSOR();
  } else if (control == IMU_accel or control == IMU_pitch) {
    setupIMU();
  }
}

void loop() {
  float voltage;
  readBATTERY(&voltage, verbose);
  controlLED(&voltage, verbose);
  // setColor(100, 100, 100);
  // Read joystick value of the switch
  int sw;
  readSWITCH(&sw, verbose);
  Serial.print("control before: ");
  Serial.println(controlMode);
  processSWITCH(sw, &controlMode, control, verbose);
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
