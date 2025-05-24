#ifndef LED_H
#define LED_H
#include <Arduino.h>

#include "constants.h"
#include "config.h"

void setupLED();
void setColor(int redValue, int greenValue, int blueValue);
void displayBlue();
void displayGreen();
void displayRed();


#endif