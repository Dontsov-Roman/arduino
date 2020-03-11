#include "MoveSensor.h"
#include "Relay.h"
#include "PhotoSensor.h"

MoveSensor::MoveSensor(Relay *rel, PhotoSensor *photo, MoveSensorMode m, int p) : relay(rel), photoSensor(photo), mode(m), pin(p)
{
  // this->relay = rel;
  // this->photoSensor = photo;
  // this->mode = m;
  // this->pin = p;
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
      digitalWrite(this->pin, HIGH);
    }
    else
    {
      digitalWrite(this->pin, LOW);
    }
    break;
  case PHOTORESISTOR:
    if (this->relay->isOn() && this->photoSensor->isOn())
    {
      digitalWrite(this->pin, HIGH);
    }
    else
    {
      digitalWrite(this->pin, LOW);
    }
  case TOGGLE:
  default:
    if (this->isOn())
    {
      digitalWrite(this->pin, LOW);
    }
    else
    {
      digitalWrite(this->pin, HIGH);
    }
    break;
  }
  this->read();
}
