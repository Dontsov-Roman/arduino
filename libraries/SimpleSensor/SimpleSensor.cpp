#include "SimpleSensor.h"

SimpleSensor::SimpleSensor()
{
}

SimpleSensor::SimpleSensor(uint8_t p)
{
    this->pin = p;
    this->enabled = false;
}
void SimpleSensor::begin()
{
    pinMode(this->pin, INPUT);
}

void SimpleSensor::read()
{
    this->enabled = digitalRead(pin) == HIGH;
}

bool SimpleSensor::isOn()
{
    return this->enabled;
}
void SimpleSensor::statusToSerial()
{
    Serial.println(this->pin);
    Serial.println(this->enabled);
}