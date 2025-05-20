#include "joystick.h"


void setupJOYSTICK(){
}

void readJOYSTICK_X(int *x, bool verbose){
    *x = analogRead(X_PIN);
    if (verbose) {
        Serial.print("X: ");
        Serial.println(*x);
    }
}


void joystickBasedStateChange(int x, State *prevState, State *currentState, bool verbose) {
    // Update state based on X-axis value
    *prevState = *currentState;
    if (x <= JOYSTICK_DOWN_THRESHOLD) {
        *currentState = DOWN;
    } else if (x >= JOYSTICK_UP_THRESHOLD) {
        *currentState = UP;
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