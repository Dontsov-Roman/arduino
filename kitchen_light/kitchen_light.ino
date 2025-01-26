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

SimpleTimeout timeout(10000);
SimpleTimeout buttonTimeout(3000);
PhotoSensor lightSensor(lightSensorPin, 750);
SimpleToggleSensor button(buttonPin, &buttonTimeout);
SimpleMovementSensor movement(movementPin, 3);
SimpleDigitalOutput output(outputPin);
KitchenLightMediator mediator(&lightSensor, &button, &movement, &output, &timeout);

void setup() {
  // SimpleTimeout timeout(3000);
  // PhotoSensor lightSensor(A1, 250);
  // SimpleSensor button = new SimpleSensor(1);
  // SimpleMovementSensor movement(2, 3);
  // SimpleDigitalOutput output(4);
  // KitchenLightMediator mediator(&lightSensor, &button, &movement, &output, &timeout);
  Serial.begin(SERIAL_BEGIN);
  mediator.begin();
  // pinMode(lightSensorPin, INPUT);
  // pinMode(buttonPin, INPUT);
  // pinMode(movementPin, INPUT);
}

void loop() {
  mediator.toggle();
  // Serial.println(analogRead(lightSensorPin));
  // Serial.println(digitalRead(buttonPin));
  // Serial.println(digitalRead(movementPin));
  // Serial.println("====================");
  // Serial.println(digitalRead(movementPin) == HIGH);
  
  Serial.println("Button:");
  button.statusToSerial();
  Serial.println("Movement:");
  movement.statusToSerial();
  Serial.println("Light:");
  lightSensor.statusToSerial();

  delay(500);
}
