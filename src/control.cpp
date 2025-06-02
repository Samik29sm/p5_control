#include "control.h"

ControlFunc controlTable[] = {
    joystickBasedStateChange,    // JOYSTICK
    flexsensorBasedStateChange,   // FLEXSENSOR
};

ControlFunc getControlFunction(ControlMode mode) {
    const int numModes = sizeof(controlTable) / sizeof(ControlFunc);
    if (mode < 0 || mode >= numModes) {
        return nullptr;
    }
    return controlTable[mode];
}

void controlMotor(ControlFunc BasedStateChangeFCT, State *prevState, State *currentState, bool verbose) {
    BasedStateChangeFCT(prevState, currentState, verbose);
    stateBasedMovement(prevState, currentState, verbose);
}