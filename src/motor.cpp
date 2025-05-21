#include "constants.h"
#include "config.h"
#include "motor.h"


void setupMOTOR(){
    // Set motor pins as outputs 
    pinMode(PWM_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
}


void motorUP( bool verbose) {
    digitalWrite(DIR_PIN, HIGH);
    analogWrite(PWM_PIN, CONSTANT_SPEED);
    if (verbose) {
        Serial.println("MOTOR UP");
    }
}

void motorDOWN(bool verbose) {
    digitalWrite(DIR_PIN, LOW);
    analogWrite(PWM_PIN, CONSTANT_SPEED);
    if (verbose) {
        Serial.println("MOTOR DOWN");
    }
}

void rampPWM(int startPWM, int endPWM, int step_size, bool direction, bool verbose){
    int step = (startPWM < endPWM) ? step_size : -step_size;
    digitalWrite(DIR_PIN, direction ? HIGH : LOW);
    for (int pwm = startPWM; pwm!= endPWM; pwm += step){
        pwm = constrain(pwm, 0, 255);
        analogWrite(PWM_PIN, pwm);
        if (verbose) {
            Serial.print("PWM: ");
            Serial.println(pwm);
        }
        delay(RAMP_DELAY);
    }
}

void rampPWMUP(bool verbose){
    rampPWM(0, CONSTANT_SPEED, STEP_SIZE_UP, true, verbose);
    if (verbose) {
        Serial.println("MOTOR UP - rampPWM");
    }
}

void rampPWMDOWN(bool verbose){
    rampPWM(0, CONSTANT_SPEED, STEP_SIZE_DOWN, false, verbose);
    if (verbose) {
        Serial.println("MOTOR DOWN - rampPWM");
    }
}

void motorREST(bool verbose) {
    digitalWrite(DIR_PIN, 0);
    analogWrite(PWM_PIN, 0);
    if (verbose) {
        Serial.println("MOTOR REST");
    }
}

void stateBasedMovement(State *prevState, State *currentState, bool verbose) {
    if (*currentState == *prevState){
        switch(*currentState) {
            case UP: motorUP(verbose); break;
            case DOWN: motorDOWN(verbose); break;
            case REST: motorREST(verbose); break;
        }
    }
    else {
        switch(*currentState) {
            case UP: rampPWMUP(verbose); break;
            case DOWN: rampPWMDOWN(verbose); break;
            case REST: motorREST(verbose); break;
        }
    }
}