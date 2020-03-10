#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(int pin, int threshold)
{
  this->pin = pin;
  this->threshold = threshold;
}
void PhotoSensor::read()
{
  this->resist = analogRead(this->pin);
  this->enabled = this->resist > this->threshold;
  Serial.print(this->resist);
  Serial.print('\n');
}