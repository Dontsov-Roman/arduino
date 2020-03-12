#include "MoveSensor.h"
#include "Relay.h"
#include "PhotoSensor.h"

MoveSensor::MoveSensor(Relay *mRel, Relay *lRel, PhotoSensor *photo, MoveSensorMode m) : moveRelay(mRel), lightRelay(lRel), photoSensor(photo), mode(m)
{
  this->bit = 0;
}

MoveSensor::MoveSensor(Relay *mRel, Relay *lRel, PhotoSensor *photo, MoveSensorMode m, int b) : moveRelay(mRel), lightRelay(lRel), photoSensor(photo), mode(m)
{
  this->bit = b;
}

void MoveSensor::setMode(MoveSensorMode mode)
{
  this->mode = mode;
}

void MoveSensor::read()
{
  this->moveRelay->read();
  this->photoSensor->read();
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
    if (this->moveRelay->isOn())
    {
      on();
    }
    else
    {
      off();
    }
    break;
  case PHOTORESISTOR:
    if (this->moveRelay->isOn() && (this->photoSensor->isOn() || this->isOn()))
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

void MoveSensor::toggle(int val)
{
  switch (mode)
  {
  case TOGGLE:
    if ((byte(val) & byte(bit)) == bit)
    {
      on();
    }
    else
    {
      off();
    }
    break;
  default:
    toggle();
    break;
  }
}

void MoveSensor::on()
{
  this->enabled = true;
  lightRelay->on();
}

void MoveSensor::off()
{
  this->enabled = false;
  lightRelay->off();
}