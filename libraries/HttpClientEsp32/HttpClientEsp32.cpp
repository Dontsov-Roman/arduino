#include "HttpClientEsp32.h"

HttpClientEsp32::HttpClientEsp32(
    const char *host,
    const char *url)
{
    this->host = host;
    this->url = url;
    this->lastResponse = ResponseStruct{};
}
HttpClientEsp32::HttpClientEsp32(
    const char *host,
    const char *url,
    const char *port)
{
    this->host = host;
    this->url = url;
    this->port = port;
    this->lastResponse = ResponseStruct{};
}

void HttpClientEsp32::begin()
{
    if (this->isSecure)
    {
        sprintf(this->fullUrl, "https://%s:%s%s", this->host, this->port, this->url);
    }
    else
    {
        sprintf(this->fullUrl, "http://%s:%s%s", this->host, this->port, this->url);
    }
    this->http.setReuse(true);
    this->setTimeout(5000);
}
ResponseStruct *HttpClientEsp32::get()
{
    char *body;
    return this->request(this->fullUrl, HTTP_METHOD_GET, body);
}
ResponseStruct *HttpClientEsp32::get(String url)
{
    char *body;
    String newUrl;
    if (this->isSecure)
    {
        newUrl += "https://";
    }
    else
    {
        newUrl += "http://";
    }
    newUrl += this->host;
    if (sizeof(this->port) > 0)
    {
        newUrl += ":";
        newUrl += this->port;
    }
    newUrl += url;
    return this->request(newUrl, HTTP_METHOD_GET, body);
}

ResponseStruct *HttpClientEsp32::get(String key, String value)
{
    char *body;
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_METHOD_GET, body);
}

ResponseStruct *HttpClientEsp32::post(char *body)
{
    return this->request(this->fullUrl, HTTP_METHOD_POST, body);
}
ResponseStruct *HttpClientEsp32::post(char *body, String key, String value)
{
    return this->request(this->generateQueryUrl(this->fullUrl, key, value), HTTP_METHOD_POST, body);
}

ResponseStruct *HttpClientEsp32::request(String url, const char *method, char *body)
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

void HttpClientEsp32::setHost(const char *host)
{
    this->host = host;
}
String HttpClientEsp32::generateQueryUrl(String url, String key, String value)
{
    String newUrl = "";
    newUrl += url;
    newUrl += "?";
    newUrl += key;
    newUrl += "=";
    newUrl += value;
    return newUrl;
}
void HttpClientEsp32::setSecure(bool isSecure)
{
    this->isSecure = isSecure;
}
void HttpClientEsp32::setTimeout(int timeout)
{
    http.setTimeout(timeout);
}