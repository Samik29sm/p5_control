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

const bool verbose = false;

// State Variables
State currentState = REST;
State prevState = REST;

ControlMode control = JOYSTICK; 
// ControlMode control = FLEXSENSOR;

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
  }
}

void loop() {
  // Read battery voltage
  float voltage;
  readBATTERY(&voltage, verbose);
  // Control LED based on battery voltage
  controlLED(&voltage, verbose);
  // Read joystick value of the switch
  int sw;
  readSWITCH(&sw, verbose);
  if (verbose) {
    Serial.print("control before: ");
    Serial.println(controlMode);
  }
  processSWITCH(sw, &controlMode, control, verbose);
  if (verbose) {
    Serial.print("control after: ");
    Serial.println(controlMode);
  }

  // Control based on the selected mode
  switch(controlMode) {
    case FLEXSENSOR: flexsensorBasedControl(&prevState, &currentState, verbose); break;
    case JOYSTICK: joystickBasedControl(&prevState, &currentState, verbose); break;
  }
  delay(100);
}
