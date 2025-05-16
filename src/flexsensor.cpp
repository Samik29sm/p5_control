#include "flexsensor.h"


void setupFLEXSENSOR() {
    // Set flex sensor pin as input
    pinMode(FLEXSENSOR_PIN, INPUT);
}

void readFLEXSENSOR(float *angle, bool verbose) {
	int ADCflex = analogRead(FLEXSENSOR_PIN);
	float Vflex = ADCflex * FLEXSENSOR_VCC / 1023.0;
	float Rflex = FLEXSENSOR_RDIV * (FLEXSENSOR_VCC / Vflex - 1.0);
	*angle = map(Rflex, FLEXSENSOR_FLATR, FLEXSENSOR_BENDR, 0, 90.0);
    if (verbose) {
        Serial.print("Flexsensor Resistance: ");
        Serial.println(Rflex);
        Serial.print("Flexsensor Angle: ");
        Serial.println(*angle);
    }
}

void flexsensorBasedStateChange(float angle, State *currentState, bool *stateChanged, bool verbose) {
    Serial.print("enter flexsensorBasedStateChange");
    if (angle <= FLEXSENSOR_THRESHOLD_UP) {
        *currentState = UP;
        *stateChanged = true;
        if (verbose) {
            Serial.print("Up: ");
            Serial.println(angle);
        }
    } else if (angle >= FLEXSENSOR_THRESHOLD_DOWN){
        *currentState = DOWN;
        *stateChanged = true;
        if (verbose) {
            Serial.print("Down: ");
            Serial.println(angle);
        }
    } else {
        if (*currentState != REST) {
            *currentState = REST;
            *stateChanged = true;
            if (verbose) {
                Serial.print("Rest: ");
                Serial.println(angle);
            }
        }
    }
}