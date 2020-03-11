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
  this->enabled = this->resist < this->threshold;
  Serial.print("\nResist:");
  Serial.print(this->resist);
  Serial.print("\nPhotoResistor enabled:");
  Serial.print(this->enabled);
}

bool PhotoSensor::isOn()
{
  return this->enabled;
}