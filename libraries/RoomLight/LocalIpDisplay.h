#ifndef LOCAL_IP_DISPLAY_H
#define LOCAL_IP_DISPLAY_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LocalIpDisplay {
    public:
        LocalIpDisplay(LiquidCrystal_I2C *lcd);
        void write(String address);
        void begin();
    protected:
        LiquidCrystal_I2C *lcd;
};

#endif
