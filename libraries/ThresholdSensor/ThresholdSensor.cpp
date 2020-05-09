#include "ThresholdSensor.h"

void ThresholdSensor::read()
{
  resist = analogRead(pin);
  enabled = resist < threshold;
}

bool ThresholdSensor::isOn()
{
  return enabled;
}

void ThresholdSensor::setThreshold(int newThreshold)
{
  threshold = newThreshold;
}