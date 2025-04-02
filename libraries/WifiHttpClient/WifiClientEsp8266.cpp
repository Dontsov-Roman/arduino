#include "WifiClientEsp8266.h"

WifiClientEsp8266::WifiClientEsp8266()
{
    this->wifiMulti = ESP8266WiFiMulti();
}
WifiClientEsp8266::WifiClientEsp8266(const char *wifiSsid,
                                     const char *wifiPassword)
{
    this->wifiSsid = wifiSsid;
    this->wifiPassword = wifiPassword;
    this->wifiMulti = ESP8266WiFiMulti();
}
void WifiClientEsp8266::begin()
{
    WiFi.mode(WIFI_STA);
    this->wifiMulti.addAP(this->wifiSsid, this->wifiPassword);
    Serial.println("Connecting to WiFi");
    while (!this->isConnected())
    {
        delay(500);
        Serial.print(".");
    }
}
bool WifiClientEsp8266::isConnected()
{
    return this->wifiMulti.run() == WL_CONNECTED;
}
String WifiClientEsp8266::getLocalIP()
{
    return WiFi.localIP().toString();
}
