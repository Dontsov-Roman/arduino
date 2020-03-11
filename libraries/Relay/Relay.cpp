#include "Relay.h"
#include "Sensor.h"

Relay ::Relay(int p, int b) : Sensor()
{
  this->pin = p;
  this->bit = b;
}
void Relay ::toggle(int val)
{
  if ((byte(val) & byte(this->bit)) == this->bit)
  {
    digitalWrite(pin, HIGH);
  }
  else
  {
    digitalWrite(pin, LOW);
  }
}
int Relay::getPin()
{
  return pin;
}
int Relay::getBit()
{
  return bit;
}
void Relay::read()
{
  this->enabled = digitalRead(this->pin);
}
bool Relay::isOn()
{
  return this->enabled;
}