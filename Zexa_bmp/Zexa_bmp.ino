#include <BmpLcd.h>
#include <LiquidCrystal.h>
#include <Adafruit_BMP280.h>
#include <SensorButton.h>

SensorButton btn(8, false);

Adafruit_BMP280 bmp280;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
BmpLcd bmpLcd(&lcd, &bmp280, &btn);

void setup() {
  // put your setup code here, to run once:
  bmpLcd.init();
}

void loop() {
  // put your main code here, to run repeatedly:

  bmpLcd.print();
}
