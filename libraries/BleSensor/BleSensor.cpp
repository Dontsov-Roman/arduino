#include "BleSensor.h"

BleSensor::BleSensor()
{
  this->buf = bleDefaultBuf;
  this->bufLength = DEFAULT_BUFFER_LENGTH;
}
BleSensor::BleSensor(char *_buf, int _bufLength)
{
  this->buf = _buf;
  this->bufLength = _bufLength;
}

bool BleSensor::isOn()
{
  return Serial.available() > 0;
}

char *BleSensor::read()
{
  if (isOn())
  {
    Serial.readBytes(buf, bufLength);
  }
  return buf;
}

void BleSensor::write(char *_buf)
{
  Serial.println(_buf);
  Serial.write(_buf);
}

char *BleSensor::getValue()
{
  return this->buf;
}