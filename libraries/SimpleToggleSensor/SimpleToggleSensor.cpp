#include <SimpleToggleSensor.h>

SimpleToggleSensor::SimpleToggleSensor() {}
SimpleToggleSensor::SimpleToggleSensor(uint8_t p, SimpleTimeout *timeout)
{
    this->pin = p;
    this->enabled = false;
    this->timeout = timeout;
}
void SimpleToggleSensor::begin()
{
    pinMode(this->pin, INPUT);
}

void SimpleToggleSensor::read()
{
    if (this->timeout->checkTimeout() && digitalRead(this->pin) == HIGH)
    {
        this->enabled = !this->enabled;
    }
}
bool SimpleToggleSensor::isOn()
{
    return this->enabled;
}

void SimpleToggleSensor::statusToSerial()
{
    Serial.println(this->pin);
    Serial.println(this->enabled);
}