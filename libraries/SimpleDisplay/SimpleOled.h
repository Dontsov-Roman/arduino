#ifndef SIMPLE_OLED_H
#define SIMPLE_OLED_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ISimpleDisplay.h>

class SimpleOled : public ISimpleDisplay
{
public:
    SimpleOled(Adafruit_SSD1306 *d)
    {
        this->display = d;
    };
    void writeFirstRow(String string);
    void writeSecondRow(String string);
    void writeThirdRow(String string);
    void begin();
    void clear();

protected:
    Adafruit_SSD1306 *display;
};
#endif
