#include <LvglEsp32.h>

LvglEsp32::LvglEsp32(
    IWifiClient *wifiClient,
    IHttpClient *gpsHttpClient,
    NtpTime *ntpTime)
{
    this->reconnectionTimeout = SimpleTimeout(10000);
    this->renderTimeout = SimpleTimeout(5000);
    this->getGpsTimeout = SimpleTimeout(15000);
    this->gpsData = GpsData();

    this->wifiClient = wifiClient;
    this->gpsHttpClient = gpsHttpClient;
    this->ntpTime = ntpTime;
}

void LvglEsp32::begin()
{
    this->gpsHttpClient->begin();
    this->ntpTime->begin();
    // Create tabs
    this->tabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 70);
    this->homeTab = lv_tabview_add_tab(this->tabs, "Home");
    this->gpsTab = lv_tabview_add_tab(this->tabs, "GPS");
    this->weatherTab = lv_tabview_add_tab(this->tabs, "Weather");
    // Create Tab Content
    this->homeContent = this->createTabContent(this->homeTab);
    this->gpsContent = this->createTabContent(this->gpsTab);
    this->weatherContent = this->createTabContent(this->weatherTab);

    this->createHomeEntities(this->homeContent);
    this->createGpsEntities(this->gpsContent);
}

lv_obj_t *LvglEsp32::createTabContent(lv_obj_t *parent)
{
    lv_obj_t *tabContent = lv_obj_create(parent);
    lv_obj_set_size(tabContent, lv_pct(100), LV_SIZE_CONTENT);
    return tabContent;
}

void LvglEsp32::createHomeEntities(lv_obj_t *parent)
{
    this->homeTimeLabel = lv_label_create(parent);
    lv_obj_set_height(this->homeTimeLabel, LV_SIZE_CONTENT);
    lv_label_set_text(this->homeTimeLabel, "Time Placeholder");
    lv_obj_t *title = lv_label_create(parent);
    lv_obj_set_height(title, LV_SIZE_CONTENT);
    lv_label_set_text(title, "Light Controll");
    lv_obj_align_to(this->homeTimeLabel, title, LV_ALIGN_OUT_BOTTOM_MID, 15, 10);

    lv_obj_t *turnOnBtn = lv_btn_create(parent);
    lv_obj_set_height(turnOnBtn, LV_SIZE_CONTENT);
    lv_obj_t *turnOnLabel = lv_label_create(turnOnBtn);
    lv_label_set_text(turnOnLabel, "Turn on light");
    lv_obj_align_to(turnOnBtn, title, LV_ALIGN_OUT_BOTTOM_MID, 10, 50);
    lv_obj_add_event_cb(turnOnBtn, eventThunk<&LvglEsp32::turnOnLight>, LV_EVENT_CLICKED, this);

    lv_obj_t *turnOffBtn = lv_btn_create(parent);
    lv_obj_set_height(turnOffBtn, LV_SIZE_CONTENT);
    lv_obj_t *turnOffLabel = lv_label_create(turnOffBtn);
    lv_label_set_text(turnOffLabel, "Turn off light");
    lv_obj_align_to(turnOffBtn, turnOnBtn, LV_ALIGN_RIGHT_MID, 200, 0);
    lv_obj_add_event_cb(turnOffBtn, eventThunk<&LvglEsp32::turnOffLight>, LV_EVENT_CLICKED, this);
}

void LvglEsp32::createGpsEntities(lv_obj_t *parent)
{
    this->gpsTimeLabel = lv_label_create(parent);
    lv_obj_set_height(this->gpsTimeLabel, LV_SIZE_CONTENT);
    lv_label_set_text(this->gpsTimeLabel, "No GPS Data");
    lv_obj_t *title = lv_label_create(parent);
    lv_obj_set_height(title, LV_SIZE_CONTENT);
    lv_label_set_text(title, "Last GPS time:");
    lv_obj_align_to(this->gpsTimeLabel, title, LV_ALIGN_OUT_BOTTOM_MID, 15, 10);
}

void LvglEsp32::turnOnLight(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        Serial.println("Light should be turned on");
        this->gpsHttpClient->get(this->turnOnLightUrl);
    }
}

void LvglEsp32::turnOffLight(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        Serial.println("Light should be turned off");
        this->gpsHttpClient->get(this->turnOffLightUrl);
    }
}

void LvglEsp32::loop()
{
    if (this->wifiClient->isConnected())
    {
        this->ntpTime->loop();
        if (this->getGpsTimeout.checkTimeout())
        {
            this->gpsData.parse(this->gpsHttpClient->get()->response);
        }
    }
    else if (this->reconnectionTimeout.checkTimeout())
    {
        this->reconnect();
    }

    if (this->renderTimeout.checkTimeout())
    {
        lv_label_set_text(this->homeTimeLabel, this->ntpTime->getDayTime());
        lv_label_set_text(this->gpsTimeLabel, this->gpsData.getGpsDateTime());
    }
}
void LvglEsp32::reconnect()
{
    this->wifiClient->begin();
}