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
    if (this->timeout->checkTimeout())
    {
        String url = "api.openweathermap.org/data/3.0/onecall";
        url += "?lat=";
        url += this->lat;
        url += "&lon=";
        url += this->lng;
        url += "&exclude=minutely,hourly&appid=";
        url += this->appId;
        deserializeJson(this->doc, this->client->get(url)->response);
    }
}
JsonDocument *OpenWeather::getLastJsonDoc()
{
    return &this->doc;
}