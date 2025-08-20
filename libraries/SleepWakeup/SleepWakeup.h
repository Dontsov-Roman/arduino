#ifndef SLEEP_WAKE_UP
#define SLEEP_WAKE_UP
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SimpleTimeout.h>
// #include <Wire.h>

#define TOUCH_IRQ GPIO_NUM_4
#define TOUCH_ADDR 0x38 // или 0x5D для GT911
class SleepWakeup
{
private:
    gpio_num_t wakeup_pin = TOUCH_IRQ;
    uint8_t wakeup_signal = 0;
    bool pullup = true;
    SimpleTimeout *sleepTimeout;
    bool byLowSignal = true;
    void clearTouchIRQ();

public:
    SleepWakeup(SimpleTimeout *sleepTimeout, gpio_num_t wakeup_pin);
    SleepWakeup(SimpleTimeout *sleepTimeout);
    bool begin();
    void loop();
};
#endif