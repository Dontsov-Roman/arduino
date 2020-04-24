#include "MoveSensor.h"
#include "Relay.h"
#include "PhotoSensor.h"

MoveSensor::MoveSensor(Relay *mRel, Relay *lRel, PhotoSensor *photo, MoveSensorMode m) : moveRelay(mRel), lightRelay(lRel), photoSensor(photo), mode(m)
{
  this->bit = 0;
}

void MoveSensor::setMode(MoveSensorMode m)
{
  mode = m;
  Serial.print("\nNew mode is:");
  Serial.print(mode);
}

void MoveSensor::read()
{
  moveRelay->read();
  photoSensor->read();
  Serial.print("\nMovement:");
  Serial.print(moveRelay->isOn());
  Serial.print("\nLight:");
  Serial.print(photoSensor->isOn());
}

bool MoveSensor::isOn()
{
  return enabled;
}
void MoveSensor::toggle()
{
  switch (mode)
  {
  case MOVEMENT:
    if (moveRelay->isOn())
    {
      on();
    }
    else
    {
      off();
    }
    break;
  case PHOTORESISTOR:
    if (moveRelay->isOn() && (photoSensor->isOn() || isOn()))
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
    if (isOn())
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
    if ((byte(val) & byte(lightRelay->getBit())) == lightRelay->getBit())
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
  enabled = true;
  lightRelay->on();
}

void MoveSensor::off()
{
  enabled = false;
  lightRelay->off();
}

void MoveSensor::setPhotoSensorThreshold(int threshold)
{
  photoSensor->setThreshold(threshold);
}