
#include <UTFT.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <MeteoLCD.h>

UTFT myGLCD(TFT32MEGA_2, 38, 39, 40, 41);

const int INPUT_PORT_TEMP = A0;

DHT dht(INPUT_PORT_TEMP, DHT11);

const int PIXEL_PER_CHAR = 14;

MeteoLCD lcd(&dht, &myGLCD, PIXEL_PER_CHAR);

void setup()
{
  Serial.begin(9600);
  lcd.init();
}
void loop()
{
  lcd.printToDisplay();
  delay(3000);
}




