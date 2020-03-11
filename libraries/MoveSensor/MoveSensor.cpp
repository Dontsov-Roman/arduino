#include "MoveSensor.h"
#include "Relay.h"
#include "PhotoSensor.h"

MoveSensor::MoveSensor(Relay *rel, PhotoSensor *photo, MoveSensorMode m, int p) : relay(rel), photoSensor(photo), mode(m), pin(p)
{
}

void MoveSensor::setMode(MoveSensorMode mode)
{
  this->mode = mode;
}

void MoveSensor::read()
{
  this->relay->read();
  this->photoSensor->read();
  this->enabled = digitalRead(this->pin);
  Serial.print("\nMovement:");
  Serial.print(enabled);
}

bool MoveSensor::isOn()
{
  return this->enabled;
}
void MoveSensor::toggle()
{
  switch (this->mode)
  {
  case MOVEMENT:
    if (this->relay->isOn())
    {
      on();
    }
    else
    {
      off();
    }
    break;
  case PHOTORESISTOR:
    if (this->relay->isOn() && this->photoSensor->isOn())
    {
      on();
    }
    else
    {
      off();
    }
    break;
  case TOGGLE:
  default:
    if (this->isOn())
    {
      on();
    }
    else
    {
      off();
    }
    break;
  }
}

void MoveSensor::on()
{
  this->enabled = true;
  digitalWrite(pin, HIGH);
}

void MoveSensor::off()
{
  this->enabled = false;
  digitalWrite(pin, LOW);
}