#include "Relay.h"
#include "Sensor.h"

Relay ::Relay(int p, int b) : Sensor()
{
  this->pin = p;
  this->bit = b;
}
void Relay::on()
{
  digitalWrite(pin, HIGH);
  this->enabled = true;
}
void Relay::off()
{
  digitalWrite(pin, LOW);
  this->enabled = false;
}
void Relay ::toggle(int val)
{
  if ((byte(val) & byte(this->bit)) == this->bit)
  {
    on();
  }
  else
  {
    off();
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