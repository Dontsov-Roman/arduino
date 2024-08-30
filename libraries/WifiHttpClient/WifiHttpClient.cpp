#include <WifiHttpClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ResponseStruct.h>
#include <ESP8266WebServer.h>

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
    sprintf(this->fullUrl, "http://%s:%s%s", this->host, this->port, this->url);
    Serial.println(this->fullUrl);
}
bool WifiHttpClient::isWifiConnected() {
    return this->wifiMulti.run() == WL_CONNECTED;
}
ResponseStruct* WifiHttpClient::get() {
    char *body;
    return this->request(this->fullUrl, HTTP_GET, body);
}

ResponseStruct* WifiHttpClient::get(char *key, char *value) {
    char *body;
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_GET, body);
}
ResponseStruct* WifiHttpClient::post(char *body) {
    return this->request(this->fullUrl, HTTP_POST, body);
}
ResponseStruct* WifiHttpClient::post(char *body, char *key, char *value) {
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_POST, body);
}

ResponseStruct* WifiHttpClient::post(char *body, const char *key, char *value) {
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_POST, body);
}

ResponseStruct* WifiHttpClient::request(char *url, HTTPMethod method, char *body) {
    if(this->isWifiConnected()) {
        if (this->http.begin(client, String(url))) {
            int httpCode;
            if(method == HTTP_POST) {
                httpCode = http.POST(body);
            } else {
                httpCode = http.GET();
            }
            this->lastResponse.code = httpCode;
            this->lastResponse.response = this->http.getString();
            
            this->http.end();
            return &this->lastResponse;
        }
    }
    this->lastResponse.code = 0;
    return &this->lastResponse;
}

void WifiHttpClient::setHost(const char* host) {
    this->host = host;
}
char* WifiHttpClient::generateQueryUrl(char *url, char *key, char *value) {
    char newUrl[128];
    strcpy(newUrl, this->fullUrl);
    strcat(newUrl, "?");
    strcat(newUrl, key);
    strcat(newUrl, "=");
    strcat(newUrl, value);
    return newUrl;
}
char* WifiHttpClient::generateQueryUrl(char *url, const char *key, char *value) {
    char newUrl[128];
    strcpy(newUrl, this->fullUrl);
    strcat(newUrl, "?");
    strcat(newUrl, key);
    strcat(newUrl, "=");
    strcat(newUrl, value);
    return newUrl;
}