#include <GpsCar.h>
#include <TinyGPSPlus.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <GpsReader.h>

GpsCar::GpsCar(
    GpsReader *gpsReader,
    WifiHttpClient *client
) {
    this->gpsReader = gpsReader;
    this->client = client;
}

void GpsCar::begin() {
    this->client->begin();
}
void GpsCar::loop() {
    this->gpsReader->readGpsData();
    Serial.println(String(this->gpsReader->getGpsData()));
}
