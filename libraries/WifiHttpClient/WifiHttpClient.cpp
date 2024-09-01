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
    this->http.setReuse(true);
}
bool WifiHttpClient::isWifiConnected() {
    return this->wifiMulti.run() == WL_CONNECTED;
}
ResponseStruct* WifiHttpClient::get() {
    char *body;
    return this->request(this->fullUrl, HTTP_GET, body);
}

ResponseStruct* WifiHttpClient::get(String key, String value) {
    char *body;
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_GET, body);
}

ResponseStruct* WifiHttpClient::post(char *body) {
    return this->request(this->fullUrl, HTTP_POST, body);
}
ResponseStruct* WifiHttpClient::post(char *body, String key, String value) {
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_POST, body);
}


ResponseStruct* WifiHttpClient::request(String url, HTTPMethod method, char *body) {
    if(this->isWifiConnected()) {
        if (this->http.begin(client, url)) {

            // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
            // this->http.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
            // this->http.addHeader("Content-Type", "text/plain");
            // this->http.addHeader("User-Agent", "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Mobile Safari/537.36");
            // this->http.addHeader("Connection", "keep-alive");
            // this->http.addHeader("Accept-Encoding", "gzip, deflate");
            // this->http.addHeader("Upgrade-Insecure-Requests", "1");
            if(method == HTTP_POST) {
                this->lastResponse.code = http.POST(body);
            } else {
                this->lastResponse.code = http.GET();
            }

            if(this->lastResponse.code > 0) {
                this->lastResponse.response = this->http.getString();
            } else {
                Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(this->lastResponse.code).c_str());
            }
            this->http.end();
            return &this->lastResponse;
        } else {
            Serial.println("[HTTP] Unable to connect");
        }
    }
    this->lastResponse.code = 0;
    this->client.flush();
    return &this->lastResponse;
}

void WifiHttpClient::setHost(const char *host) {
    this->host = host;
}
String WifiHttpClient::generateQueryUrl(String url, String key, String value) {
    String newUrl = "";
    newUrl += url;
    newUrl += "?";
    newUrl += key;
    newUrl += "=";
    newUrl += value;
    Serial.println(newUrl);
    return newUrl;
}
String WifiHttpClient::getLocalIP() {
    return WiFi.localIP().toString();
}