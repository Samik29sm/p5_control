#include "battery.h"


void setupBATTERY(){
}

void readBATTERY(float *voltage, bool verbose){
    float adcValue = analogRead(BATTERY_PIN);
    *voltage = (adcValue / 1023.0) * 5.0; // Convertisseur analogique sur 5 bits
}

void controlLED(float *voltage, bool verbose) {
    if (verbose) {
        Serial.print("Battery voltage: ");
        Serial.println(*voltage);
    }

    if (*voltage < BATTERY_THRESHOLD_EMPTY) {
        displayRed();
        if (verbose) {
            Serial.println("Battery voltage is low");
        }
    } 
    else if (*voltage < BATTERY_THRESHOLD_MEDIUM) {
        displayBlue();
        if (verbose) {
            Serial.println("Battery voltage is sufficient");
        }
    }
    else {
        displayGreen();
        if (verbose) {
            Serial.println("Battery voltage is good");
        }
    }
}
