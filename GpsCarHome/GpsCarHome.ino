#include <GpsCar.h>
#include <SoftwareSerial.h>
#include <GpsReader.h>
#include <SimpleOled.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ResponseStruct.h>
#include <WifiClientEsp32.h>
#include <HttpClientEsp32.h>
#include <GpsData.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SimpleOled simpleOled(&display);

#ifndef STASSID
// #define STASSID "UFI-495947"
// #define STAPSK "12345678"
// #define STASSID "car_wifi"
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define HOST "195.78.246.46"
#define PORT "8080"
#define URL "/set-gps"
#endif

const char *wifiSsid = STASSID;
const char *wifiPassword = STAPSK;
const char *host = HOST;
const char *port = PORT;
const char *url = URL;

SoftwareSerial ss(5, 6);
GpsReader gpsReader(&ss);
GpsData gpsData;
WifiClientEsp32 wifiClient(wifiSsid, wifiPassword);
HttpClientEsp32 httpClient(host, url, port);

GpsCar gpsCar(&gpsReader, &wifiClient, &httpClient, &simpleOled, 20000);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  wifiClient.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
  }

  gpsCar.begin();
}

void loop()
{
  gpsCar.loop();
}
