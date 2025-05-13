#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "imu.h"

// Instantiate the BNO055 object
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);


void setupIMU() {
    if (!bno.begin()) {
        Serial.println("Error: BNO055 not detected");
        while (1);
    }
    Serial.println("BNO055 initialized successfully");
    delay(500);
    bno.setExtCrystalUse(true);
}

bool calibration(bool gyroBasedCalibration, bool accelBasedCalibration, bool magBasedCalibration, bool verbose) {
    uint8_t system_cal, gyro, accel, mag;
    bno.getCalibration(&system_cal, &gyro, &accel, &mag);
    bool gyroCalibrated = !gyroBasedCalibration || (gyro == 3);
    bool accelCalibrated = !accelBasedCalibration || (accel == 3);
    bool magCalibrated = !magBasedCalibration || (mag == 3);
    if (gyroCalibrated && accelCalibrated && magCalibrated) {
        return true;
    }
    else {
        if (verbose) {
            Serial.print("Calibration - Sys:");
            Serial.print(system_cal);
            Serial.print(" Gyro:");
            Serial.print(gyro);
            Serial.print(" Accel:");
            Serial.print(accel);
            Serial.print(" Mag:");
            Serial.println(mag); 
        }
        return false;
    }
}

float readAccel() {
    imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    float rawAccZ = acc.z(); 
    return rawAccZ;
}

float readPitch() {
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    float pitch = euler.y();
    return pitch;
}

void accelBasedStateChange (float accZ, State *currentState, bool *stateChanged, bool verbose) {
    if (accZ > IMU_ACCEL_THRESHOLD_CHANGE_HIGH){
      *currentState = UP;
      *stateChanged = true;
      if (verbose) {
        Serial.print("Up: ");
        Serial.println(accZ);
      }
    }
    else if (accZ < IMU_ACCEL_THRESHOLD_CHANGE_LOW){
      *currentState = DOWN;  
      *stateChanged = true;
      if (verbose) {
        Serial.print("Down: ");
        Serial.println(accZ);
      }
    }
    else if (accZ < IMU_ACCEL_THRESHOLD_REST_HIGH or accZ > IMU_ACCEL_THRESHOLD_REST_LOW){
      if (*currentState != REST){
        *currentState = REST;  
        *stateChanged = true;
        if (verbose) {
          Serial.print("Rest: ");
          Serial.println(accZ);
        }
      }
    }
}

void pitchBasedStateChange(float rawPitch, float prevPitch, State *currentState, bool *stateChanged, bool verbose) {
    float diffPitch = abs(prevPitch) - abs(rawPitch);

    if (diffPitch < 0 && abs(diffPitch) > IMU_PITCH_THRESHOLD_MOVE) {
      *currentState = UP;
      *stateChanged = true;
      if (verbose) {
        Serial.print("Up: ");
        Serial.println(rawPitch);
      }
    }
    else if (diffPitch > 0 && abs(diffPitch) > IMU_PITCH_THRESHOLD_MOVE){
      *currentState = DOWN;  
      *stateChanged = true;
      if (verbose) {
        Serial.print("Down: ");
        Serial.println(rawPitch);
      }
    }
    else if (abs(diffPitch) < IMU_PITCH_THRESHOLD_REST){
      if (*currentState != REST){
        *currentState = REST;  
        *stateChanged = true;
        if (verbose) {
          Serial.print("Rest: ");
          Serial.println(rawPitch);
        }
      }
    }
}

