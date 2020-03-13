#include "BleSensor.h"
#include "Sensor.h"

BleSensor::BleSensor() {}

bool BleSensor::isOn()
{
  return Serial.available() > 0;
}

void BleSensor::read()
{
  if (isOn())
  {
    Serial.readBytes(buf, BUFFER_LENGTH);
  }
}

char *BleSensor::getValue()
{
  return this->buf;
}