#include <BleRtcSetter.h>

BleRtcSetter::BleRtcSetter(BleSensor *_ble, iarduino_RTC *_rtc)
{
  this->ble = _ble;
  this->rtc = _rtc;
}

void BleRtcSetter::setTime()
{
  this->ble->read();
  char *time = this->ble->getValue();
  // String seconds = String(time[0]) + String(time[1]);
  String minutes = String(time[2]) + String(time[3]);
  String hours = String(time[4]) + String(time[5]);
  String date = String(time[6]) + String(time[7]);
  String month = String(time[8]) + String(time[9]);
  String year = String(time[10]) + String(time[11]);
  String dayOfWeek = String(time[12]) + String(time[13]);
  this->rtc->settime(0, minutes.toInt(), hours.toInt(), date.toInt(), month.toInt(), year.toInt(), dayOfWeek.toInt());
}