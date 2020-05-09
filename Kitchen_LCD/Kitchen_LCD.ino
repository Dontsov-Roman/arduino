#include <LiquidCrystal.h>
#include <Adafruit_BMP280.h>
#include <iarduino_RTC.h>

Adafruit_BMP280 bmp280;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int LED_PIN = 2;


float temperature;
float pressure;
float altitude;
void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  lcd.begin(16, 2);


//  while (!bmp280.begin(BMP280_ADDRESS - 1)) {
//    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
//    delay(2000);
//  }

}

void loop() {
  temperature = bmp280.readTemperature();
  pressure = bmp280.readPressure();
  altitude = bmp280.readAltitude(1013.25);

  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.print(" *C;");
  
  lcd.print(pressure);
  lcd.print(" Pa;");
  
  lcd.setCursor(0, 1);
  lcd.print(altitude);
  lcd.print(" m;");

  delay(5000);
}
