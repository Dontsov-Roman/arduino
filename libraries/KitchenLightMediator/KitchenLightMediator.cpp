#include <KitchenLightMediator.h>

KitchenLightMediator::KitchenLightMediator(
    PhotoSensor *lightSensor,
    SimpleToggleSensor *button,
    SimpleMovementSensor *movementSensor,
    SimpleDigitalOutput *output,
    SimpleDigitalOutput *buttonIndicator,
    SimpleTimeout *timeout)
{
    this->lightSensor = lightSensor;
    this->button = button;
    this->movementSensor = movementSensor;
    this->output = output;
    this->timeout = timeout;
    this->buttonIndicator = buttonIndicator;
}

void KitchenLightMediator::begin()
{
    this->button->begin();
    this->lightSensor->begin();
    this->output->begin();
    this->buttonIndicator->begin();
    this->movementSensor->begin();
    this->movementSensor->calibrate();
}

void KitchenLightMediator::toggle()
{
    bool previousButtonState = this->button->isOn();

    this->button->read();
    this->lightSensor->read();
    this->movementSensor->read();

    if (this->button->isOn())
    {
        this->buttonIndicator->switchOn();
        this->output->switchOn();
        return;
    }
    else if (previousButtonState)
    {
        this->buttonIndicator->switchOff();
        this->output->switchOff();
        this->timeout->checkTimeout();
        return;
    }
    if (!this->movementSensor->isOn())
    {
        if (this->timeout->checkTimeout())
        {
            this->output->switchOff();
        }
    }
    if (!this->output->isOn() && this->movementSensor->isOn() && this->lightSensor->isOn())
    {
        if (this->timeout->checkTimeout())
        {
            this->output->switchOn();
        }
    }
}