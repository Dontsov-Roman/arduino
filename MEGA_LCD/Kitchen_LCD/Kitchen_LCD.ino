#include "KitchenLcd.h"
#include "BleSensor.h"
#include <SensorButton.h>

SensorButton btn(8, true);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

iarduino_RTC rtc(RTC_DS1302, 10, 12, 11);

DHT dht(A0, DHT11);

KitchenLcd kLcd(&lcd, &rtc, &dht, &btn);

BleSensor BS;

void setup() {
  Serial.begin(9600);
//  rtc.settime(0, 48, 13, 11, 5, 20, 1);
  kLcd.init();
}

void loop() {
  kLcd.print();
  delay(1000);
}
