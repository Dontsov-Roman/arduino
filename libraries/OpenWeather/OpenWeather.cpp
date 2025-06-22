#include <OpenWeather.h>

OpenWeather::OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId)
{
    this->client = client;
    this->timeout = timeout;
    this->appId = appId;
}

void OpenWeather::setCoords(char *lat, char *lng)
{
    this->lat = lat;
    this->lng = lng;
}

void OpenWeather::getWeather()
{
    String url;
    url += "?lat=";
    url += this->lat;
    url += "&lon=";
    url += this->lng;
    url += "&appid=";
    url += this->appId;
    deserializeJson(this->doc, this->client->get(url)->response);
}

void OpenWeather::loop()
{

    if (this->timeout->checkTimeout())
    {
        this->getWeather();
    }
}

JsonDocument *OpenWeather::getLastJsonDoc()
{
    return &this->doc;
}