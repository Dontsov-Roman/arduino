#include "KitchenLcd.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

iarduino_RTC rtc(RTC_DS1302, 12, 10, 11);

DHT dht(A0, DHT11);

KitchenLcd kLcd(&lcd, &rtc, &dht);

void setup() {
  Serial.begin(9600);
  kLcd.init();
}

void loop() {
  kLcd.print();
  delay(5000);
}
