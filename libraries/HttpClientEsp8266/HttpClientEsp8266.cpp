#include "HttpClientEsp8266.h"

HttpClientEsp8266::HttpClientEsp8266(
    const char *host,
    const char *url,
    const char *port)
{
    this->host = host;
    this->url = url;
    this->port = port;
    this->lastResponse = ResponseStruct{};
}

void HttpClientEsp8266::begin()
{
    sprintf(this->fullUrl, "http://%s:%s%s", this->host, this->port, this->url);
    this->http.setReuse(true);
}
ResponseStruct *HttpClientEsp8266::get()
{
    char *body;
    return this->request(this->fullUrl, HTTP_METHOD_GET, body);
}

ResponseStruct *HttpClientEsp8266::get(String key, String value)
{
    char *body;
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_METHOD_GET, body);
}

ResponseStruct *HttpClientEsp8266::post(char *body)
{
    return this->request(this->fullUrl, HTTP_METHOD_POST, body);
}
ResponseStruct *HttpClientEsp8266::post(char *body, String key, String value)
{
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_METHOD_POST, body);
}

ResponseStruct *HttpClientEsp8266::request(String url, const char *method, char *body)
{
    if (this->http.begin(this->client, url))
    {

        if (method == HTTP_METHOD_POST)
        {
            this->lastResponse.code = http.POST(body);
        }
        else
        {
            this->lastResponse.code = http.GET();
        }

        if (this->lastResponse.code > 0)
        {
            this->lastResponse.response = this->http.getString();
        }
        else
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(this->lastResponse.code).c_str());
        }
        this->http.end();
        return &this->lastResponse;
    }
    else
    {
        Serial.println("[HTTP] Unable to connect");
    }
    this->lastResponse.code = 0;
    this->client.flush();
    return &this->lastResponse;
}

void HttpClientEsp8266::setHost(const char *host)
{
    this->host = host;
}
String HttpClientEsp8266::generateQueryUrl(String url, String key, String value)
{
    String newUrl = "";
    newUrl += url;
    newUrl += "?";
    newUrl += key;
    newUrl += "=";
    newUrl += value;
    return newUrl;
}