#include <OpenWeather.h>

OpenWeather::OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId)
{
    this->client = client;
    this->timeout = timeout;
    this->appId = appId;
}

OpenWeather::OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId, const char *urlVersion)
{
    this->client = client;
    this->timeout = timeout;
    this->appId = appId;
    this->urlVersion = urlVersion;
}

void OpenWeather::setCoords(char *lat, char *lng)
{
    this->lat = lat;
    this->lng = lng;
}

void OpenWeather::getWeather()
{
    String url;
    url += this->urlVersion;
    url += "?lat=";
    url += this->lat;
    url += "&lon=";
    url += this->lng;
    url += "&appid=";
    url += this->appId;
    url += "&units=metric";
    url += "&cnt=1";
    deserializeJson(this->doc, this->client->get(url)->response);
}

void OpenWeather::loop()
{

    if (this->timeout->checkTimeout())
    {
        this->getWeather();
    }
}

void OpenWeather::serializeToSerial()
{
    Serial.println("");
    serializeJson(this->doc, Serial);
    Serial.println("");
    Serial.println(this->getLastTemperature());
    Serial.println(this->getLastWeather());
}
String OpenWeather::getLastTemperature()
{

    double temp_min = this->doc["list"][0]["main"]["temp_min"];
    double temp_max = this->doc["list"][0]["main"]["temp_max"];

    char min[50];
    char max[50];
    dtostrf(temp_min, 4, 2, min);
    dtostrf(temp_max, 4, 2, max);
    String weather;
    weather += "Temp: ";
    weather += temp_min;
    weather += "-";
    weather += max;
    weather += " C";
    return weather;
}
String OpenWeather::getLastWeather()
{
    return String(this->doc["list"][0]["weather"][0]["description"]);
}

JsonDocument *OpenWeather::getLastJsonDoc()
{
    return &this->doc;
}