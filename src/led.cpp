#include "led.h"

#include "constants.h"
#include "config.h"


void setupLED() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void setColor(int redValue, int greenValue, int blueValue) {
    analogWrite(RED_PIN, redValue);
    analogWrite(GREEN_PIN, greenValue);
    analogWrite(BLUE_PIN, blueValue);
}

void displayBlue() {
    setColor(0, 0, LED_DISPLAY); // Orange: Red + half Green
}

void displayGreen() {
    setColor(0, LED_DISPLAY, 0); // Green
}

void displayRed() {
    setColor(LED_DISPLAY, 0, 0); // Red
}

