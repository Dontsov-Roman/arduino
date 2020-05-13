#include <BleRtcSetter.h>

BleRtcSetter::BleRtcSetter(BleSensor *_ble, iarduino_RTC *_rtc)
{
  this->ble = _ble;
  this->rtc = _rtc;
}

void BleRtcSetter::setTime()
{
  if (ble->isOn())
  {
    char *time = ble->read();
    if (time[0] == BIT_SET)
    {
      String minutes = String(time[3]) + String(time[4]);
      String hours = String(time[5]) + String(time[6]);
      String date = String(time[7]) + String(time[8]);
      String month = String(time[9]) + String(time[10]);
      String year = String(time[11]) + String(time[12]);
      String dayOfWeek = String(time[13]);
      rtc->settime(0, minutes.toInt(), hours.toInt(), date.toInt(), month.toInt(), year.toInt(), dayOfWeek.toInt());
    }
  }
}