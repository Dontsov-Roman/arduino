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
}
bool WifiClientEsp8266::isConnected()
{
    return true;
}
String WifiClientEsp8266::getLocalIP()
{
    return String();
}