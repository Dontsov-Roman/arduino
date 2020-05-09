#include <LiquidCrystal.h>
#include <Adafruit_BMP280.h>
#include <iarduino_RTC.h>

Adafruit_BMP280 bmp280;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

iarduino_RTC time(RTC_DS1302, 12, 10, 11);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  time.begin();

}

void loop() {

  lcd.setCursor(0, 1);
  lcd.print(bmp280.readTemperature());
  lcd.print(" *C;");

  lcd.print(bmp280.readPressure());
  lcd.print(" Pa;");

  delay(5000);
}
