#include "PhotoSensor.h"
#include "Sensor.h"

PhotoSensor::PhotoSensor(int p, int t) : pin(p), threshold(t)
{
}
void PhotoSensor::read()
{
  resist = analogRead(pin);
  enabled = resist < threshold;
  Serial.print("\nResist:");
  Serial.print(resist);
  Serial.print("\nThreshold:");
  Serial.print(threshold);
}

bool PhotoSensor::isOn()
{
  return enabled;
}

void PhotoSensor::setThreshold(int newThreshold)
{
  threshold = newThreshold;
}