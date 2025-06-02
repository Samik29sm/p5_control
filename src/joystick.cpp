#include "joystick.h"


void setupJOYSTICK(){
}

void readJOYSTICK_Y(int *y, bool verbose){
    *y = analogRead(Y_PIN);
    if (verbose) {
        Serial.print("Y: ");
        Serial.println(*y);
    }
}


void joystickBasedStateChange(State *prevState, State *currentState, bool verbose) {
    // Read y value
    int y;
    readJOYSTICK_Y(&y, verbose);
    // Update state based on Y-axis value
    *prevState = *currentState;
    if (y <= JOYSTICK_DOWN_THRESHOLD) {
        *currentState = DOWN;
    } else if (y >= JOYSTICK_UP_THRESHOLD) {
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