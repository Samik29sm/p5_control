#include "switch.h"

void setupSWITCH(){
    pinMode(SW_PIN, INPUT);
    digitalWrite(SW_PIN, HIGH);
}

void readSWITCH(int *sw, bool verbose){
    *sw = analogRead(SW_PIN);

    if (verbose) {
        Serial.print(" SW: ");
        Serial.println(*sw);
    }
}

void processSWITCH(int sw, ControlMode *controlMode, ControlMode control, bool verbose){
    // Switch control mode if switch is pressed
    if (sw == LOW) {
        *controlMode = JOYSTICK;
    }
    else {
        *controlMode = control;
    }
    
    if (verbose) {
        Serial.print("Control Mode:");
        switch (*controlMode){
            case FLEXSENSOR: Serial.println("FLEXSENSOR"); break;
            case JOYSTICK: Serial.println("JOYSTICK"); break;
        }
    }
}