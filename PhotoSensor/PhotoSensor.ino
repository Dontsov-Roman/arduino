#include "PhotoSensor.h"
const int PHOTO_PORT = A0;
const int threshold = 100;
PhotoSensor PS(PHOTO_PORT, threshold);

void setup() {
  pinMode(PHOTO_PORT, INPUT);
  Serial.begin(9600);
}

void loop() {
  PS.read();
  delay(1000);
}
