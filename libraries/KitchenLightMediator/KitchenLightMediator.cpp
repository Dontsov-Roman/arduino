#include <KitchenLightMediator.h>

KitchenLightMediator::KitchenLightMediator(
    PhotoSensor *lightSensor,
    SimpleToggleSensor *button,
    SimpleMovementSensor *movementSensor,
    SimpleDigitalOutput *output,
    SimpleTimeout *timeout)
{
    this->lightSensor = lightSensor;
    this->button = button;
    this->movementSensor = movementSensor;
    this->output = output;
    this->timeout = timeout;
}

void KitchenLightMediator::begin()
{
    this->button->begin();
    this->lightSensor->begin();
    this->output->begin();
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
        this->output->switchOn();
        return;
    }
    else if (previousButtonState)
    {
        this->output->switchOff();
        this->timeout->checkTimeout();
        return;
    }
    if (this->timeout->checkTimeout())
        if (
            this->movementSensor->isOn() &&
            ((!this->output->isOn() && this->lightSensor->isOn()) || this->output->isOn()))
        {
            {
                this->output->switchOn();
            }
        }
        else
        {

            this->output->switchOff();
        }
}