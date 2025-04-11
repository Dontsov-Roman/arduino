#ifndef SIMPLE_DISPLAY_SWITCHER_H
#define SIMPLE_DISPLAY_SWITCHER_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ISimpleDisplay.h>

class SimpleDisplaySwitcher
{
public:
    SimpleDisplaySwitcher() {};
    SimpleDisplaySwitcher(ISimpleDisplay *display)
    {
        this->display = display;
    };
    void writeFirstRow(String firstString, String secondString);
    void writeSecondRow(String firstString, String secondString);
    void writeThirdRow(String firstString, String secondString);
    void switchDisplay();

protected:
    ISimpleDisplay *display;
    int displayCase = 0;
};
#endif