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

void flexsensorBasedStateChange(State *prevState, State *currentState, bool verbose) {
    float angle;
    readFLEXSENSOR(&angle, verbose);
    if (angle <= FLEXSENSOR_THRESHOLD_UP) {
        *currentState = UP;
    } else if (angle >= FLEXSENSOR_THRESHOLD_DOWN){
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
        Serial.print("Angle: ");
        Serial.println(angle);
    }
}
