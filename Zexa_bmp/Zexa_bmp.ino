#include <BmpLcd.h>
#include <LiquidCrystal.h>
#include <Adafruit_BMP280.h>
#include <SensorButton.h>

SensorButton btn(8, true);

Adafruit_BMP280 bmp280;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
BmpLcd bmpLcd(&lcd, &bmp280, &btn);

void setup() {
  Serial.begin(9600);
  bmpLcd.init();
}

void loop() {
  bmpLcd.print();
  delay(1000);
}
