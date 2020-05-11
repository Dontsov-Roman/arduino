#include <SensorButton.h>

SensorButton::SensorButton(uint8_t _pin)
{
  this->pin = _pin;
  this->value = false;
}

SensorButton::SensorButton(uint8_t _pin, bool defaultValue)
{
  this->pin = _pin;
  this->value = defaultValue;
}

void SensorButton::init()
{
  pinMode(pin, INPUT);
}

void SensorButton::read()
{
  if (digitalRead(pin))
  {
    while (digitalRead(pin))
    {
    }
    value = !value;
  }
}

bool SensorButton::isOn()
{
  return value;
}