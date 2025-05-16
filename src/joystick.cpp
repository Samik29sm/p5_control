#include "joystick.h"


void setupJOYSTICK(){
    pinMode(SW_PIN, INPUT);
    digitalWrite(SW_PIN, HIGH);
}

void readJOYSTICK_X(int *x, bool verbose){
    *x = analogRead(X_PIN);
    if (verbose) {
        Serial.print("X: ");
        Serial.println(*x);
    }
}

void readJOYSTICK_SW(int *sw, bool verbose){
    *sw = analogRead(SW_PIN);

    if (verbose) {
        Serial.print(" SW: ");
        Serial.println(*sw);
    }
}

void processJOYSTICK(int sw, ControlMode *controlMode, ControlMode control, bool verbose) {
    // Switch control mode if switch is pressed
    if (sw == LOW) {
        if (*controlMode != control){
            *controlMode = control;
        }
        else {
            *controlMode = JOYSTICK;
        }
    }
    if (verbose) {
        Serial.print("Control Mode:");
        switch (*controlMode){
            case FLEXSENSOR: Serial.println("FLEXSENSOR"); break;
            case IMU_accel: Serial.println("IMU_accel"); break;
            case IMU_pitch: Serial.println("IMU_pitch"); break; 
            case JOYSTICK: Serial.println("JOYSTICK"); break;
        }
    }
}

void joystickBasedStateChange(int x, State *prevState, State *currentState, bool verbose) {
    // Update state based on X-axis value
    *prevState = *currentState;
    if (x >= JOYSTICK_UP_THRESHOLD_LOW && x <= JOYSTICK_UP_THRESHOLD_HIGH) {
        *currentState = UP;
    } else if (x >= JOYSTICK_DOWN_THRESHOLD_LOW && x <= JOYSTICK_DOWN_THRESHOLD_HIGH) {
        *currentState = DOWN;
    } else {
        *currentState = REST;
    }

    if (verbose && *currentState != *prevState) {
        switch (*currentState) {
            case UP: Serial.println("State: UP"); break;
            case DOWN: Serial.println("State: DOWN"); break;
            case REST: Serial.println("State: REST"); break;
        }
    }
}