#include <TFT_HX8357.h>
#include <UTFT.h>
#include <DHT.h>

TFT_HX8357 tft = TFT_HX8357();
UTFT myGLCD(ILI9486, 38, 39, 40, 41);

extern uint8_t BigFont[];

const int INPUT_PORT_TEMP = A0;
DHT dht(INPUT_PORT_TEMP, DHT11);
const char temperature[] = "Temperature: ";
const char humidity[] = "Humidity: ";
char temp[2];
char hum[2];
const int PIXEL_PER_CHAR = 14;
const int tempX = sizeof(temperature)*PIXEL_PER_CHAR;
const int humX = sizeof(humidity)*PIXEL_PER_CHAR;

void setup()
{
  dht.begin();
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(1);
  myGLCD.InitLCD(1);
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);

}
void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  dtostrf(t, 2, 2, temp);
  myGLCD.print(temperature, LEFT, 0);
  myGLCD.print(temp, tempX, 0);
  dtostrf(h, 2, 2, hum);
  myGLCD.print(humidity, LEFT, PIXEL_PER_CHAR);
  myGLCD.print(hum, humX, PIXEL_PER_CHAR);
  delay(3000);
}
