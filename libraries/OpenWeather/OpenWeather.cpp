#include <OpenWeather.h>

OpenWeather::OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId)
{
    this->client = client;
    this->timeout = timeout;
    this->appId = appId;
}

OpenWeather::OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId, const char *urlVersion, int cnt)
{
    this->client = client;
    this->timeout = timeout;
    this->appId = appId;
    this->urlVersion = urlVersion;
    this->cnt = cnt;
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
    if (this->cnt > 0)
    {
        url += "&cnt=";
        url += String(this->cnt);
    }
    deserializeJson(this->doc, this->client->get(url)->response);
    this->findMinMaxTemp();
}

void OpenWeather::findMinMaxTemp()
{
    this->temp_min = this->doc["list"][0]["main"]["temp_min"];
    this->temp_max = this->doc["list"][0]["main"]["temp_max"];
    int count = this->doc["count"];
    for (int i = 0; i < count; i++)
    {
        double t_min = this->doc["list"][i]["main"]["temp_min"];
        double t_max = this->doc["list"][i]["main"]["temp_max"];
        if (this->temp_min > t_min && t_min != 0)
        {
            this->temp_min = t_min;
        }
        if (this->temp_max < t_max && t_max != 0)
        {
            this->temp_max = t_max;
        }
    }
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
    String weather;
    weather += "Temp: ";
    weather += this->temp_min;
    weather += "-";
    weather += this->temp_max;
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