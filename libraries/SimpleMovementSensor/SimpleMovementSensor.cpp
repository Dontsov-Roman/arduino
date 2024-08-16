#include "SimpleMovementSensor.h"

SimpleMovementSensor::SimpleMovementSensor() {
    this->calibrationTime = SIMPLE_MOVEMENT_SENSOR_DEFAULT_CALIBRATION_TIME;
}
SimpleMovementSensor::SimpleMovementSensor(uint8_t p) {
    this->pin = p;
    this->calibrationTime = SIMPLE_MOVEMENT_SENSOR_DEFAULT_CALIBRATION_TIME;
}
// c - calibration time in seconds
SimpleMovementSensor::SimpleMovementSensor(uint8_t p, int c) {
    this->pin = p;
    this->calibrationTime = c;
}
void SimpleMovementSensor::calibrate() {
    for(int i = 0; i < this->calibrationTime; i++){
      Serial.print(".");
      delay(1000);
    }
    Serial.println(" done");
    Serial.println("MOVEMENT SENSOR ACTIVE");
    delay(50);
}