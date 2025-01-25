#include "ThresholdSensor.h"

void ThresholdSensor::begin()
{
  pinMode(this->pin, INPUT);
}
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
void ThresholdSensor::statusToSerial()
{
  Serial.println(this->pin);
  Serial.println(this->resist);
  Serial.println(this->enabled);
}