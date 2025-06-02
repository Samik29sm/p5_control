#include "control.h"

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



void joystickBasedControl(State *prevState, State *currentState, bool verbose) {
    int y;
    readJOYSTICK_Y(&y, verbose);
    joystickBasedStateChange(y, prevState, currentState, verbose);
    stateBasedMovement(prevState, currentState, verbose);
}