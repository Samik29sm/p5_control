#include "constants.h"
#include "config.h"
#include "motor.h"


void setupMOTOR(){
    // Set motor pins as outputs 
    pinMode(PWM_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
}

void motorUP( bool verbose=false) {
    digitalWrite(DIR_PIN, HIGH);
    analogWrite(PWM_PIN, CONSTANT_SPEED);
    if (verbose) {
        Serial.println("MOTOR UP");
    }
}

void motorDOWN(bool verbose=false) {
    digitalWrite(DIR_PIN, LOW);
    analogWrite(PWM_PIN, CONSTANT_SPEED);
    if (verbose) {
        Serial.println("MOTOR DOWN");
    }
}

void motorREST(bool verbose=false) {
    digitalWrite(DIR_PIN, 0);
    if (verbose) {
        Serial.println("MOTOR REST");
    }
}

void stateBasedMovement(State currentState) {
    switch(currentState) {
        case UP: motorUP; break;
        case DOWN: motorDOWN; break;
        case REST: motorREST; break;
    }
}