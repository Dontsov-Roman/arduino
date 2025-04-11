#ifndef I_SIMPLE_OLED_H
#define I_SIMPLE_OLED_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
class ISimpleDisplay
{
public:
    virtual void writeFirstRow(String address);
    virtual void writeSecondRow(String address);
    virtual void writeThirdRow(String address);
    virtual void begin();
    virtual void clear();
};
#endif