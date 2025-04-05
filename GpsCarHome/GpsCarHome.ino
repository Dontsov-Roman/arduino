// #include <GpsCar.h>
#include <SoftwareSerial.h>
#include <GpsReader.h>
// #include <SimpleOled.h>

// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

#include <WifiClientEsp32.h>
#include <HttpClientEsp32.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// SimpleOled simpleOled(&display);

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
WifiClientEsp32 wifiClient(wifiSsid, wifiPassword);
HttpClientEsp32 httpClient(&wifiClient, host, url, port);

// GpsCar gpsCar(&gpsReader, &httpClient, &simpleOled);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  wifiClient.begin();
  // simpleOled.begin();
  // httpClient.begin();
  // if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  // {
  //   Serial.println(F("SSD1306 allocation failed"));
  // }

  // gpsCar.begin();
}

void loop()
{
  // display.clearDisplay();
  // display.setTextSize(1); // Draw 2X-scale text
  // display.setTextColor(SSD1306_WHITE);
  // display.setCursor(0, 0);
  // display.println(F("initializing..."));
  // display.display();
  gpsReader.readGpsData();
  if (gpsReader.isReady()){
    Serial.println("Date/time:");
    Serial.println(gpsReader.getGpsDateTime());
    Serial.println("Coordinates:");
    Serial.println(gpsReader.getGpsLatLng());
  } else {
    Serial.println("No gps connection");
  }
  if(wifiClient.isConnected()){
    Serial.println("Local IP:");
    Serial.println(wifiClient.getLocalIP());
    // simpleOled.writeFirstRow(wifiClient.getLocalIP());
  } else {
    Serial.println('No connection to wifi');
  }
  delay(1000);
  // gpsCar.loop();
}
