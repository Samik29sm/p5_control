#include <Arduino.h>
#include <Wire.h>

#include "constants.h"
#include "config.h"
#include "control.h"
#include "motor.h"
#include "joystick.h"
#include "flexsensor.h"
#include "switch.h"
#include "led.h"
#include "battery.h"

// State Variables
State currentState = REST;
State prevState = REST;

ControlMode controlMode = DEFAULT_CONTROL;

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_SPEED);

  setupMOTOR();
  setupSWITCH();
  setupJOYSTICK();
  setupLED();
  setupBATTERY();
  if (DEFAULT_CONTROL == FLEXSENSOR) {
    setupFLEXSENSOR();
  }
}

void loop() {
  // Read battery voltage
  float voltage;
  readBATTERY(&voltage, VERBOSE);
  // Control LED based on battery voltage
  controlLED(&voltage, VERBOSE);
  // Read joystick value of the switch
  int sw;
  readSWITCH(&sw, VERBOSE);
  if (VERBOSE) {
    Serial.print("control before: ");
    Serial.println(controlMode);
  }
  processSWITCH(sw, &controlMode, DEFAULT_CONTROL, VERBOSE);
  if (VERBOSE) {
    Serial.print("control after: ");
    Serial.println(controlMode);
  }

  // Control based on the selected mode
  ControlFunc controlFunction = getControlFunction(controlMode);
  if (controlFunction) {
    controlMotor(controlFunction, &prevState, &currentState, VERBOSE);
  } 
  else {
    Serial.println("Invalid control function");
  }
  delay(100);
}
