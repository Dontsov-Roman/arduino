#include "PhotoSensor.h"
#include "Sensor.h"

PhotoSensor::PhotoSensor(int p, int t)
{
  this->pin = p;
  this->threshold = t;
}
void PhotoSensor::read()
{
  this->resist = analogRead(this->pin);
  this->enabled = this->resist < this->threshold;
}

bool PhotoSensor::isOn()
{
  return this->enabled;
}