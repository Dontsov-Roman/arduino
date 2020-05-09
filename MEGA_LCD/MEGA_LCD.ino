#include <MeteoLCD.h>
#include <GasSensor.h>
#include <PhotoSensor.h>

const int INPUT_PORT_TEMP = A0;
const int PIXEL_PER_CHAR = 14;
const int GAS_PORT = A1;

UTFT display(TFT32MEGA_2, 38, 39, 40, 41);

iarduino_RTC rtc(1, 5, 6, 7);


DHT dht(INPUT_PORT_TEMP, DHT11);

GasSensor gasSensor(GAS_PORT);

MeteoLCD lcd(&dht, &display, &rtc, &gasSensor, PIXEL_PER_CHAR);

void setup()
{
  Serial.begin(9600);
  lcd.init();
}
void loop()
{
  lcd.print();
  delay(3000);
}
