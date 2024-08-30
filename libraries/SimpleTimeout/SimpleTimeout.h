#ifndef SIMPLE_TIMEOUT_H
#define SIMPLE_TIMEOUT_H
#define SIMPLE_DEFAULT_TIMEOUT 5000;
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class SimpleTimeout {
    public:
        SimpleTimeout();
        SimpleTimeout(int timeout);
        bool checkTimeout();
    protected:
        int timeout;
        int lastUpdateMillis;
        int currentMilSec;
};

#endif