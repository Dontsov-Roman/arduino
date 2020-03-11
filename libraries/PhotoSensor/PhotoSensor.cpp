#include "PhotoSensor.h"
#include "Sensor.h"

PhotoSensor::PhotoSensor(int pin, int threshold) : Sensor()
{
  this->pin = pin;
  this->threshold = threshold;
}
void PhotoSensor::read()
{
  this->resist = analogRead(this->pin);
  this->enabled = this->resist > this->threshold;
}

bool PhotoSensor::isOn()
{
  return this->enabled;
}