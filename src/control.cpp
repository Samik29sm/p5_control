#include "control.h"

float prevPitch = 0.0; // Previous pitch value for IMU-based control
float prevAccel = 0.0; // Previous acceleration value for IMU-based control

void flexsensorBasedControl(State *prevState, State *currentState, bool verbose) {
    float angle;
    bool stateChanged = false;
    readFLEXSENSOR(&angle, verbose);
    flexsensorBasedStateChange(angle, currentState, &stateChanged, verbose);
    Serial.println(stateChanged);
    if (stateChanged) {
        stateBasedMovement(prevState, currentState, verbose);
        *prevState = *currentState;
    }
}

void accelBasedControl(State *prevState, State *currentState, bool verbose) {
    if (calibration(false, true, false, verbose)) {
        float accel = readAccel();
        bool stateChanged = false;
        accelBasedStateChange(accel, currentState, &stateChanged, verbose);
        if (stateChanged) {
            *prevState = *currentState;
            stateBasedMovement(prevState, currentState);
        }
        prevAccel = accel; 
    }
    else {
        Serial.println("IMU not calibrated");
    }
}


void pitchBasedControl(State *prevState, State *currentState, bool verbose) {
    if (calibration(true, false, false, verbose)) {
        float pitch = readPitch();
        bool stateChanged = false;
        pitchBasedStateChange(pitch, prevPitch, currentState, &stateChanged, verbose);
        if (stateChanged) {
            *prevState = *currentState;
            stateBasedMovement(prevState, currentState, verbose);
        }
        prevPitch = pitch;
    }
    else {
        Serial.println("IMU not calibrated");
    }
}

void joystickBasedControl(State *prevState, State *currentState, bool verbose) {
    int x;
    readJOYSTICK_X(&x, verbose);
    joystickBasedStateChange(x, prevState, currentState, verbose);
    stateBasedMovement(prevState, currentState, verbose);
}