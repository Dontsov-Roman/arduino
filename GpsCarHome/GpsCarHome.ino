#include <WifiClientEsp32.h>
#include <HttpClientEsp32.h>
#include <GpsHomeDisplay.h>
#include <SimpleOled.h>
#include <SimpleToggleSensor.h>
#include <SimpleTimeout.h>
#include <NtpTime.h>
#include <OpenWeather.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#ifndef STASSID
// #define STASSID "UFI-495947"
// #define STAPSK "12345678"
// #define STASSID "car_wifi"
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define HOST "195.78.246.46"
#define PORT "8080"
#define URL "/get-gps"
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET 7200
#define DAY_LIGHT_OFFSET 3600
#define OPEN_WEATHER_API_KEY "9a77f4e52681be3d74817619d3689c73"
#define OPEN_WEATHER_HOST "api.openweathermap.org"
#define OPEN_WEATHER_PORT "80"
#define OPEN_WEATHER_URL "data/2.5/forecast"
#define OPEN_WEATHER_LAT "46.403395"
#define OPEN_WEATHER_LNG "30.721698"
#endif

const char *wifiSsid = STASSID;
const char *wifiPassword = STAPSK;
const char *host = HOST;
const char *port = PORT;
const char *url = URL;
const char *ntpServer = NTP_SERVER;
const long gmtOffset = GMT_OFFSET;
const int dayLightOffset = DAY_LIGHT_OFFSET;

const char *openWeatherHost = OPEN_WEATHER_HOST;
const char *openWeatherUrl = OPEN_WEATHER_URL;
const char *openWeatherPort = OPEN_WEATHER_PORT;
const char *openWeatherApiKey = OPEN_WEATHER_API_KEY;
char *openWeatherLat = OPEN_WEATHER_LAT;
char *openWeatherLng = OPEN_WEATHER_LNG;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SimpleOled simpleOled(&display);
WifiClientEsp32 wifiClient(wifiSsid, wifiPassword);
HttpClientEsp32 httpClient(host, url, port);
HttpClientEsp32 httpClientOW(openWeatherHost, openWeatherUrl, openWeatherPort);

SimpleTimeout buttonTimeout(1000);
SimpleTimeout gpsTimeout(120000);
SimpleTimeout initializationTimeout(15000);
SimpleTimeout displaySwitchTimeout(5000);
SimpleTimeout reconnectionTimeout(30000);
SimpleTimeout ntpTimer(30000);
SimpleTimeout openWeatherTimer(15 * 60 * 1000);
// SimpleTimeout serializeTimeout(15000);

OpenWeather openWeather(&httpClientOW, &openWeatherTimer, openWeatherApiKey);
NtpTime ntpTime(&ntpTimer, ntpServer, gmtOffset, dayLightOffset);
SimpleToggleSensor button(3, &buttonTimeout);

GpsHomeDisplay gpsHomeDisplay(
    &wifiClient,
    &httpClient,
    &simpleOled,
    &button,
    &ntpTime,
    &openWeather,
    &gpsTimeout,
    &initializationTimeout,
    &displaySwitchTimeout,
    &reconnectionTimeout);

void setup()
{
  Serial.begin(115200);
  wifiClient.begin();
  openWeather.setCoords(openWeatherLat, openWeatherLng);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
  }
  gpsHomeDisplay.begin();
}

void loop()
{
  gpsHomeDisplay.loop();
  // if (serializeTimeout.checkTimeout()) {
  //   openWeather.serializeToSerial();
  // }
}
