#include <WifiHttpClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ResponseStruct.h>

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
    this->lastResponse = ResponseStruct{};
    this->wifiMulti = ESP8266WiFiMulti();
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
    sprintf(this->fullUrl, "%s:%s%s", this->host, this->port, this->url);
}
bool WifiHttpClient::isWifiConnected() {
    return this->wifiMulti.run() == WL_CONNECTED;
}
ResponseStruct* WifiHttpClient::get() {
    if(this->isWifiConnected()) {
        if (this->http.begin(wifi, String(this->fullUrl))) {
            int httpCode = http.GET();
            this->lastResponse.code = httpCode;
            this->lastResponse.response = this->http.getString();
            
            this->http.end();
            return &this->lastResponse;
        }
    }
    this->lastResponse.code = 0;
    return &this->lastResponse;
}
ResponseStruct* WifiHttpClient::post(char *body) {
    if(this->isWifiConnected()) {
        if (http.begin(wifi, String(this->fullUrl))) {
            int httpCode = http.POST(body);
            this->lastResponse.code = httpCode;
            this->lastResponse.response = this->http.getString();
            this->http.end();
           
            return &this->lastResponse;
        }
    }
    this->lastResponse.code = 0;
    return &this->lastResponse;
}