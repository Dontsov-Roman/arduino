#include "WifiClientEsp32.h"

WifiClientEsp32::WifiClientEsp32()
{
    this->wifiMulti = WiFiMulti();
}
WifiClientEsp32::WifiClientEsp32(const char *wifiSsid,
                                 const char *wifiPassword)
{
    this->wifiSsid = wifiSsid;
    this->wifiPassword = wifiPassword;
    this->wifiMulti = WiFiMulti();
}
void WifiClientEsp32::begin()
{
    WiFi.mode(WIFI_STA);
    this->wifiMulti.addAP(this->wifiSsid, this->wifiPassword);
    Serial.println("Connecting to WiFi");
    while (!this->isConnected())
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("Connected");
}
bool WifiClientEsp32::isConnected()
{
    return this->wifiMulti.run() == WL_CONNECTED;
}
String WifiClientEsp32::getLocalIP()
{
    return WiFi.localIP().toString();
}
