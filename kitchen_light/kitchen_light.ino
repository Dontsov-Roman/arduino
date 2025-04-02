#include <KitchenLightMediator.h>
#include <PhotoSensor.h>
#include <SimpleToggleSensor.h>
#include <SimpleDigitalOutput.h>
#include <SimpleMovementSensor.h>
#include <SimpleTimeout.h>

#define SERIAL_BEGIN 9600

uint8_t buttonPin = 5;
uint8_t movementPin = 3;
uint8_t lightSensorPin = A1;
uint8_t outputPin = 4;
uint8_t buttonIndicatorPin = 8;

SimpleTimeout timeout(10000);
SimpleTimeout buttonTimeout(5000);
PhotoSensor lightSensor(lightSensorPin, 750);
SimpleToggleSensor button(buttonPin, &buttonTimeout);
SimpleMovementSensor movement(movementPin, 3);
SimpleDigitalOutput output(outputPin);
SimpleDigitalOutput buttonIndicator(buttonIndicatorPin);
KitchenLightMediator mediator(&lightSensor, &button, &movement, &output, &buttonIndicator, &timeout);

void setup()
{
  Serial.begin(SERIAL_BEGIN);
  mediator.begin();
}

void loop()
{
  mediator.toggle();
}
