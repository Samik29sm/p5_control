#include "control.h"

float prevPitch = 0.0; // Previous pitch value for IMU-based control
float prevAccel = 0.0; // Previous acceleration value for IMU-based control

void flexsensorBasedControl(State *prevSate, State *currentState, bool verbose) {
    float angle;
    bool stateChanged = false;
    readFLEXSENSOR(&angle, verbose);
    flexsensorBasedStateChange(angle, currentState, &stateChanged, verbose);
    if (stateChanged) {
        *prevSate = *currentState;
        stateBasedMovement(*currentState);
    }
}

void accelBasedControl(State *prevSate, State *currentState, bool verbose) {
    if (calibration(false, true, false, verbose)) {
        float accel = readAccel();
        bool stateChanged = false;
        accelBasedStateChange(accel, currentState, &stateChanged, verbose);
        if (stateChanged) {
            *prevSate = *currentState;
            stateBasedMovement(*currentState);
        }
        prevAccel = accel; 
    }
    else {
        Serial.println("IMU not calibrated");
    }
}


void pitchBasedControl(State *prevSate, State *currentState, bool verbose) {
    if (calibration(true, false, false, verbose)) {
        float pitch = readPitch();
        bool stateChanged = false;
        pitchBasedStateChange(pitch, prevPitch, currentState, &stateChanged, verbose);
        if (stateChanged) {
            *prevSate = *currentState;
            stateBasedMovement(*currentState);
        }
        prevPitch = pitch;
    }
    else {
        Serial.println("IMU not calibrated");
    }
}

void joystickBasedControl(State *prevSate, State *currentState, bool verbose) {
    int x;
    readJOYSTICK_X(&x, verbose);
    joystickBasedStateChange(x, prevSate, currentState);
    stateBasedMovement(*currentState);
}