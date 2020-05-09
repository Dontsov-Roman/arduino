#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(uint8_t p)
{
  this->pin = p;
  this->threshold = 7;
}

PhotoSensor::PhotoSensor(uint8_t p, int t)
{
  this->pin = p;
  this->threshold = t;
}