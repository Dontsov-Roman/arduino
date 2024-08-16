#include "SimpleDigitalOutput.h"

SimpleDigitalOutput::SimpleDigitalOutput() {
}
SimpleDigitalOutput::SimpleDigitalOutput(uint8_t p) {
    this->pin = p;
    this->enabled = false;
}
void SimpleDigitalOutput::begin() {
    pinMode(this->pin, OUTPUT);
}
void SimpleDigitalOutput::switchOn() {
    digitalWrite(this->pin, HIGH);
    this->enabled = true;
}
void SimpleDigitalOutput::switchOff() {
    digitalWrite(this->pin, LOW);
    this->enabled = false;
}