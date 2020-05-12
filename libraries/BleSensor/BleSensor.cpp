#include "BleSensor.h"

BleSensor::BleSensor()
{
  isCustomBuf = false;
}
BleSensor::BleSensor(char *_buf, int _bufLength)
{
  this->customBuf = _buf;
  this->bufLength = _bufLength;
  isCustomBuf = true;
}

bool BleSensor::isOn()
{
  return Serial.available() > 0;
}

void BleSensor::read()
{
  if (isOn())
  {
    if (isCustomBuf)
    {
      Serial.readBytes(customBuf, bufLength);
    }
    else
    {
      Serial.readBytes(buf, BUFFER_LENGTH);
    }
  }
}

char *BleSensor::getValue()
{
  if (isCustomBuf)
  {
    return this->customBuf;
  }
  else
  {
    return this->buf;
  }
}