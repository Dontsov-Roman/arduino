#include "PhotoSensor.h"
#include "Relay.h"
const int PHOTO_PIN = A0;
const int THRESHOLD_PHOTO = 100;
const int LIGHT_PIN = D7;
const int LINGHT_BIT = 1;
PhotoSensor PS(PHOTO_PIN, THRESHOLD_PHOTO);
Relay Rel(LIGHT_PIN, LINGHT_BIT);

void setup() {
  pinMode(PHOTO_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  PS.read();
  Rel.read();
  Serial.println(PS.isOn());
  delay(1000);
}
