#include "PhotoSensor.h"
#include "Relay.h"
#include "MoveSensor.h"

const int PHOTO_PIN = A0;
const int THRESHOLD_PHOTO = 10;
const int LIGHT_PIN = LED_BUILTIN;
const int MOVE_BIT = 1;
const int MOVE_PIN = D5;
PhotoSensor PS(PHOTO_PIN, THRESHOLD_PHOTO);
Relay Rel(MOVE_PIN, MOVE_BIT);
MoveSensor MS(&Rel, &PS, PHOTORESISTOR, LIGHT_PIN);

void setup() {
  pinMode(PHOTO_PIN, INPUT);
  pinMode(MOVE_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  MS.read();
  MS.toggle();
  delay(2000);
}
