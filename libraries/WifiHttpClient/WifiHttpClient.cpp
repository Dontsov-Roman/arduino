#include <WifiHttpClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

WifiHttpClient::WifiHttpClient(
    const char *wifiSsid,
    const char *wifiPassword,
    const char *host,
    const char *url,
    const char *port
){
    this->wifiSsid = wifiSsid;
    this->wifiPassword = wifiPassword;
    this->host = host;
    this->url = url;
    this->port = port;
    this->wifiMulti = ESP8266WiFiMulti();
    // this->fullUrl;
    sprintf(this->fullUrl, "%s:%s%s", this->host, this->port, this->url);
}

void WifiHttpClient::begin(){
    WiFi.mode(WIFI_STA);
    this->wifiMulti.addAP(this->wifiSsid, this->wifiPassword);
    Serial.println("Connecting to WiFi");
    while (!this->isWifiConnected()) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());
}
bool WifiHttpClient::isWifiConnected() {
    return this->wifiMulti.run() == WL_CONNECTED;
}
int WifiHttpClient::get() {
    if(this->isWifiConnected()) {
        if (http.begin(wifi, String(this->fullUrl))) {
            int httpCode = http.GET();
            return httpCode;
        }
    }
    return 0;
}
int WifiHttpClient::post() {
    return 0;
}