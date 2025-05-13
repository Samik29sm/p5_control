#include "joystick.h"


void setupJOYSTICK(){
    pinMode(SW_PIN, INPUT);
    digitalWrite(SW_PIN, HIGH);
}

void readJOYSTICK(int *x, int *y, int *sw, bool verbose=false){
    *x = analogRead(X_PIN);
    *y = analogRead(Y_PIN);
    *sw = digitalRead(SW_PIN);

    if (verbose) {
        Serial.print("X: ");
        Serial.print(*x);
        Serial.print(" Y: ");
        Serial.print(*y);
        Serial.print(" SW: ");
        Serial.println(*sw);
    }
}

void processJOYSTICK(int x, int sw, bool *prevSwitchState, bool *controlMode, ControlMode control, State *prevState, State *currentState, bool verbose=false) {
    // Switch control mode if switch is pressed
    if (sw == LOW && *prevSwitchState == HIGH) {
        *controlMode = JOYSTICK;
        if (verbose) {
            Serial.println("Control Mode: Joystick");
        }
    }
    else if (sw == HIGH && *prevSwitchState == LOW) {
        *controlMode = control;
        if (verbose) {
            Serial.print("Control Mode:");
        Serial.println(control == FLEXSENSOR ? " Flexsensor" : " IMU");
        }
    }
    *prevSwitchState = sw;

    // Update state based on X-axis value

    if (x >= JOYSTICK_UP_THRESHOLD_LOW && x <= JOYSTICK_UP_THRESHOLD_HIGH) {
        *currentState = UP;
    } else if (x >= JOYSTICK_DOWN_THRESHOLD_LOW && x <= JOYSTICK_DOWN_THRESHOLD_HIGH) {
        *currentState = DOWN;
    } else {
        *currentState = REST;
    }
    *prevState = *currentState;

    if (verbose && *currentState != *prevState) {
        switch (*currentState) {
            case UP: Serial.println("State: UP"); break;
            case DOWN: Serial.println("State: DOWN"); break;
            case REST: Serial.println("State: REST"); break;
        }
    }
}