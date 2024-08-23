#include <GpsCar.h>
#include <TinyGPSPlus.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

GpsCar::GpsCar(
    SoftwareSerial *ss,
    const char *wifiSsid,
    const char *wifiPassword,
    const char *host,
    const char *url,
    const char *port
) {
    this->gps = TinyGPSPlus();
    this->ss = ss;
    this->wifiSsid = wifiSsid;
    this->wifiPassword = wifiPassword;
    this->host = host;
    this->url = url;
    this->port = port;
    this->gpsReadDelay = DEFAULT_GPS_READ_DELAY;
}

void GpsCar::begin() {
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(this->wifiSsid, this->wifiPassword);
    Serial.println("Connecting to WiFi");
    while (WiFiMulti.run() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}
void GpsCar::loop() {
    this->readGpsData();
    this->getGpsDateTime();
    this->getGpsLatLng();
}

void GpsCar::readGpsData() {
  unsigned long start = millis();
  do 
  {
    while (ss->available())
      gps.encode(ss->read());
  } while (millis() - start < this->gpsReadDelay);
}

char* GpsCar::getGpsData() {
    char gpsAllData[64];
    return gpsAllData;
}
char* GpsCar::getGpsDateTime() {
    if (this->gps.date.isValid() && this->gps.time.isValid()) {
        sprintf(
            this->dateTime,
            "%02d/%02d/%02d %02d:%02d:%02d",
            this->gps.date.month(),
            this->gps.date.day(),
            this->gps.date.year(),
            this->gps.time.hour(),
            this->gps.time.minute(),
            this->gps.time.second()
        );
    }
    Serial.println(this->dateTime);
    
    return this->dateTime;
}
char* GpsCar::getGpsLatLng() {
    if (this->gps.location.isValid()) {
        // sprintf(this->latLng, "%f, %f", this->gps.location.lat(), this->gps.location.lng());
        Serial.println("dtostrf");
        // Serial.println(dtostrf(this->gps.location.lat(), 4, 6, this->lat));
        dtostrf(this->gps.location.lat(), 4, 10, this->lat);
        dtostrf(this->gps.location.lng(), 4, 10, this->lng);
        Serial.println(this->lat);
        Serial.println(this->lng);
        sprintf(this->latLng, "%s,%s", this->lat, this->lng);
        Serial.println(this->latLng);
    }
    
    return this->lat;
}