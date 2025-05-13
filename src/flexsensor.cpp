#include "flexsensor.h"


void setupFLEXSENSOR() {
    // Set flex sensor pin as input
    pinMode(FLEXSENSOR_PIN, INPUT);
}

void readFLEXSENSOR(int *value, bool verbose=false) {
    // Read the flex sensor value
    *value = analogRead(FLEXSENSOR_PIN);
    if (verbose) {
        Serial.print("Flexsensor Value: ");
        Serial.println(*value);
    }


    // Read the ADC, and calculate voltage and resistance from it
	int ADCflex = analogRead(FLEXSENSOR_PIN);
	float Vflex = ADCflex * FLEXSENSOR_VCC / 1023.0;
	float Rflex = FLEXSENSOR_RDIV * (FLEXSENSOR_VCC / Vflex - 1.0);
	Serial.println("Resistance: " + String(Rflex) + " ohms");

	// Use the calculated resistance to estimate the sensor's bend angle:
	float angle = map(Rflex, FLEXSENSOR_FLATR, FLEXSENSOR_BENDR, 0, 90.0);
	Serial.println("Bend: " + String(angle) + " degrees");
	Serial.println();
}