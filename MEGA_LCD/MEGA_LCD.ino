#include <MeteoLCD.h>
#include <GasSensor.h>
#include <PhotoSensor.h>
#include <Adafruit_BMP280.h>

const int PIXEL_PER_CHAR = 14;
const int GAS_PORT = A1;

Adafruit_BMP280 bmp280;

UTFT display(TFT32MEGA_2, 38, 39, 40, 41);

iarduino_RTC rtc(1, 5, 6, 7);


GasSensor gasSensor(GAS_PORT);

MeteoLCD lcd(&display, &bmp280, &rtc, &gasSensor, PIXEL_PER_CHAR);

void setup()
{
  Serial.begin(9600);
//  rtc.settime(0, 48, 19, 20, 5, 20, 3);
  lcd.init();
}
void loop()
{
  lcd.print();
  delay(3000);
}
