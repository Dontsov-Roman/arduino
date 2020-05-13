#include "KitchenLcd.h"
#include "BleSensor.h"
#include <SensorButton.h>
#include <BleRtcSetter.h>

SensorButton btn(8, true);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

iarduino_RTC rtc(RTC_DS1302, 10, 12, 11);

DHT dht(A0, DHT11);

KitchenLcd kLcd(&lcd, &rtc, &dht, &btn);

const int bufLength = 14;
char buf[bufLength];

BleSensor BS(buf, &bufLength);

BleRtcSetter brs(&BS, &rtc);

void setup() {
  Serial.begin(9600);
    rtc.settime(0, 48, 13, 11, 5, 20, 1);
  kLcd.init();
}

void loop() {
  kLcd.print();
  brs.setTime();
  delay(1000);
}
