#ifndef LOCAL_IP_DISPLAY_H
#define LOCAL_IP_DISPLAY_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ISimpleDisplay.h>

class LocalIpDisplay : public ISimpleDisplay {
    public:
        LocalIpDisplay(LiquidCrystal_I2C *display);
        void writeFirstRow(String address);
        void writeSecondRow(String address);
        void begin();
        void clear();
    protected:
        LiquidCrystal_I2C *display;
};

#endif
