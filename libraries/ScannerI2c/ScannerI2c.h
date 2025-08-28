#ifndef SCANNER_I2C
#define SCANNER_I2C
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <Wire.h>

class ScannerI2c
{
public:
    static void scan(int sda, int scl)
    {
        TwoWire W = TwoWire(1);
        Serial.printf("\nScanning on SDA=%d SCL=%d\n", sda, scl);
        W.begin(sda, scl);

        byte count = 0;
        for (byte addr = 1; addr < 127; addr++)
        {
            W.beginTransmission(addr);
            if (W.endTransmission() == 0)
            {
                Serial.printf("Found device at 0x%02X\n", addr);
                count++;
            }
        }
        if (count == 0)
        {
            Serial.println("No I2C devices found");
        }
        else
        {
            Serial.printf("Fount %s devices", count);
        }
    }
    static void scanFromTo(int start, int end)
    {
        int sda = start;
        int scl;
        while (sda < end)
        {
            scl = sda + 1;
            ScannerI2c::scan(sda, scl);
            sda++;
            delay(100);
        }
    }
};
#endif