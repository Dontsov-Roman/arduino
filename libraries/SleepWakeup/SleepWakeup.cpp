#include <SleepWakeup.h>

SleepWakeup::SleepWakeup(SimpleTimeout *sleepTimeout, gpio_num_t wakeup_pin)
{
    this->wakeup_pin = wakeup_pin;
    this->sleepTimeout = sleepTimeout;
}
SleepWakeup::SleepWakeup(SimpleTimeout *sleepTimeout)
{
    this->sleepTimeout = sleepTimeout;
}

bool SleepWakeup::begin()
{
    delay(300);
    auto cause = esp_sleep_get_wakeup_cause();
    bool wakeup_by_touch_or_power = false;
    Serial.printf("TP_IRQ level after delay: %d\n", digitalRead(TOUCH_IRQ));
    Serial.printf("wakeup pin level after delay: %d\n", digitalRead(this->wakeup_pin));
    if ((this->byLowSignal && cause == ESP_SLEEP_WAKEUP_EXT1) || (!this->byLowSignal && cause == ESP_SLEEP_WAKEUP_EXT0))
    {
        this->sleepTimeout->checkTimeout();
        Serial.println("Wake by touch IRQ");
        wakeup_by_touch_or_power = true;
    }
    else if (cause == ESP_SLEEP_WAKEUP_TIMER)
    {
        this->sleepTimeout->checkTimeout();
        Serial.println("Wake by timer");
    }
    else
    {
        this->sleepTimeout->checkTimeout();
        Serial.println("Power-on / reset");
        wakeup_by_touch_or_power = true;
    }

    if (this->pullup)
        pinMode(this->wakeup_pin, INPUT_PULLUP);

    if (this->byLowSignal)
        esp_sleep_enable_ext0_wakeup(this->wakeup_pin, this->wakeup_signal);
    else
        esp_sleep_enable_ext1_wakeup(1ULL << this->wakeup_pin, ESP_EXT1_WAKEUP_ALL_LOW);
    return wakeup_by_touch_or_power;
}

void SleepWakeup::loop()
{
    if (this->sleepTimeout->checkTimeout())
    {
        while (digitalRead(this->wakeup_pin) == LOW)
        {
            delay(10);
        }
        Serial.println("Go to sleep...");
        delay(300);
        esp_deep_sleep_start();
    }
}
// void SleepWakeup::clearTouchIRQ()
// {
// Wire.beginTransmission(TOUCH_ADDR);
// Wire.write(0x02); // регистр "точек"
// Wire.endTransmission(false);
// Wire.requestFrom(TOUCH_ADDR, 1);
// if (Wire.available())
// {
//     uint8_t n = Wire.read(); // число точек
//     (void)n;                 // можно игнорировать
// }
// }