#include <HomeLvgl.h>

HomeLvgl::HomeLvgl(
    IWifiClient *wifiClient,
    IHttpClient *gpsHttpClient,
    NtpTime *ntpTime,
    OpenWeather *openWeather)
{
    this->reconnectionTimeout = SimpleTimeout(10000);
    this->renderTimeout = SimpleTimeout(5000);
    this->getGpsTimeout = SimpleTimeout(15000);
    this->gpsData = GpsData();

    this->wifiClient = wifiClient;
    this->gpsHttpClient = gpsHttpClient;
    this->ntpTime = ntpTime;
    this->openWeather = openWeather;
}

void HomeLvgl::begin()
{
    this->gpsHttpClient->begin();
    this->ntpTime->begin();
    this->openWeather->begin();
    this->openWeather->getWeather();
    // Create tabs
    this->tabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 70);
    this->homeTab = lv_tabview_add_tab(this->tabs, "Home");
    this->weatherTab = lv_tabview_add_tab(this->tabs, "Weather");
    // Create Tab Content
    this->gpsContent = this->createTabContent(this->homeTab);
    this->homeContent = this->createTabContent(this->homeTab);

    this->createHomeEntities(this->homeContent);
    this->createGpsEntities(this->gpsContent);
    this->createWeatherEntities();

    lv_obj_align_to(this->gpsContent, this->homeContent, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
}

lv_obj_t *HomeLvgl::createTabContent(lv_obj_t *parent)
{
    lv_obj_t *tabContent = lv_obj_create(parent);
    lv_obj_set_size(tabContent, lv_pct(100), LV_SIZE_CONTENT);
    return tabContent;
}

void HomeLvgl::createHomeEntities(lv_obj_t *parent)
{
    lv_obj_t *title = lv_label_create(parent);
    this->homeTimeLabel = lv_label_create(parent);
    lv_obj_set_height(title, LV_SIZE_CONTENT);
    lv_label_set_recolor(title, true);
    lv_obj_set_height(this->homeTimeLabel, LV_SIZE_CONTENT);
    lv_label_set_text(title, "#0000ff Light Controll");
    lv_obj_align_to(this->homeTimeLabel, title, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    lv_obj_t *turnOnBtn = lv_btn_create(parent);
    lv_obj_set_height(turnOnBtn, LV_SIZE_CONTENT);
    lv_obj_t *turnOnLabel = lv_label_create(turnOnBtn);
    lv_label_set_text(turnOnLabel, "Turn on light");
    lv_obj_align_to(turnOnBtn, this->homeTimeLabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_obj_add_event_cb(turnOnBtn, eventThunk<&HomeLvgl::turnOnLight>, LV_EVENT_CLICKED, this);

    lv_obj_t *turnOffBtn = lv_btn_create(parent);
    lv_obj_set_height(turnOffBtn, LV_SIZE_CONTENT);
    lv_obj_t *turnOffLabel = lv_label_create(turnOffBtn);
    lv_label_set_text(turnOffLabel, "Turn off light");
    lv_obj_align_to(turnOffBtn, turnOnBtn, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_obj_add_event_cb(turnOffBtn, eventThunk<&HomeLvgl::turnOffLight>, LV_EVENT_CLICKED, this);
}

void HomeLvgl::createGpsEntities(lv_obj_t *parent)
{
    this->gpsTimeLabel = lv_label_create(parent);
    lv_obj_set_height(this->gpsTimeLabel, LV_SIZE_CONTENT);
    lv_label_set_recolor(this->gpsTimeLabel, true);
    lv_label_set_text(this->gpsTimeLabel, "#ff0000 No GPS Data");
    lv_obj_t *title = lv_label_create(parent);
    lv_obj_set_height(title, LV_SIZE_CONTENT);
    lv_label_set_recolor(title, true);
    lv_label_set_text(title, "#0000ff Last GPS time:");
    lv_obj_align_to(this->gpsTimeLabel, title, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    lv_obj_t *coordsLabel = lv_label_create(parent);
    lv_obj_set_height(coordsLabel, LV_SIZE_CONTENT);
    lv_label_set_recolor(coordsLabel, true);
    lv_label_set_text(coordsLabel, "#0000ff Last Coordinates:");
    lv_obj_align_to(coordsLabel, title, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    this->gpsCoordsLabel = lv_label_create(parent);
    lv_obj_set_height(this->gpsCoordsLabel, LV_SIZE_CONTENT);
    lv_obj_align_to(this->gpsCoordsLabel, coordsLabel, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
}

void HomeLvgl::createWeatherEntities()
{
    this->weatherContent = this->createTabContent(this->weatherTab);
    this->temperatureLabel = lv_label_create(this->weatherContent);
    lv_obj_set_height(this->temperatureLabel, LV_SIZE_CONTENT);
    lv_label_set_text(this->temperatureLabel, "Min-max temperature");

    this->weatherDescriptionLabel = lv_label_create(this->weatherContent);
    lv_obj_set_height(this->weatherDescriptionLabel, LV_SIZE_CONTENT);
    lv_label_set_text(this->weatherDescriptionLabel, "Weather description placeholder");

    lv_obj_align_to(this->weatherDescriptionLabel, this->temperatureLabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    this->weatherTile[0].begin(this->weatherTab);
    lv_obj_align_to(this->weatherTile[0].getContainer(), this->weatherContent, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
    for (int i = 1; i < 3; ++i)
    {
        this->weatherTile[i].begin(this->weatherTab);
        lv_obj_align_to(this->weatherTile[i].getContainer(), this->weatherTile[i - 1].getContainer(), LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    }
}

void HomeLvgl::turnOnLight(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        Serial.println("Light should be turned on");
        this->gpsHttpClient->get(this->turnOnLightUrl);
    }
}

void HomeLvgl::turnOffLight(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        Serial.println("Light should be turned off");
        this->gpsHttpClient->get(this->turnOffLightUrl);
    }
}
void HomeLvgl::render()
{
    lv_label_set_text(this->homeTimeLabel, this->ntpTime->getDayTime());
    lv_label_set_text(this->gpsTimeLabel, this->gpsData.getGpsDateTime());
    lv_label_set_text(this->gpsCoordsLabel, this->gpsData.getGpsLatLng());
    lv_label_set_text(this->temperatureLabel, this->openWeather->getLastTemperature());
    lv_label_set_text(this->weatherDescriptionLabel, this->openWeather->getLastWeather());

    this->renderWeatherTiles();
}
void HomeLvgl::renderWeatherTiles()
{
    JsonDocument *doc = this->openWeather->getLastJsonDoc();
    int count = (*doc)["cnt"];
    for (int i = 0; i < count; ++i)
    {
        double temp_min = (*doc)["list"][i]["main"]["temp_min"];
        double temp_max = (*doc)["list"][i]["main"]["temp_max"];
        const char *date = (*doc)["list"][i]["dt_txt"].as<const char *>();
        const char *desc = (*doc)["list"][i]["weather"][0]["description"].as<const char *>();
        this->weatherTile[i].setDate(date);
        this->weatherTile[i].setMinTemp(temp_min);
        this->weatherTile[i].setMaxTemp(temp_max);
        this->weatherTile[i].setWeatherDesc(desc);
    }
}
void HomeLvgl::loop()
{
    if (this->wifiClient->isConnected())
    {
        this->ntpTime->loop();
        this->openWeather->loop();
        if (this->getGpsTimeout.checkTimeout())
        {
            this->gpsData.parse(this->gpsHttpClient->get()->response);
        }
    }
    else if (this->reconnectionTimeout.checkTimeout())
    {
        this->wifiClient->begin();
    }

    if (this->renderTimeout.checkTimeout())
    {
        this->render();
    }
}