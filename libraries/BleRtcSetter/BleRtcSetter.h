#ifndef BLE_RTC_SETTER_H
#define BLE_RTC_SETTER_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <BleSensor.h>
#include <iarduino_RTC.h>

#define BIT_SET '9'
class BleRtcSetter
{
public:
  BleRtcSetter(BleSensor *_ble, iarduino_RTC *_rtc);
  void setTime();

protected:
  BleSensor *ble;
  iarduino_RTC *rtc;
};
#endif
