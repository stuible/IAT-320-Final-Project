// Acc Libraries
#include <ArduinoJson.h> //https://arduinojson.org/v6/example/parser/

#include "Transmit.h"

Transmit transmit;

int objectChannel = 4;
int baseChannel = 1;

const int prevTrackPin = 1;
const int nextTrackPin =  0;
const int volumeUpPin = 6;
const int volumeDownPin = 12;
const int pausePin = 3;

void setup() {
  Serial.begin(9600);

  transmit = Transmit(objectChannel, baseChannel);

}
void loop() {
  transmit.receive();

//  transmit.send("track", "next");

buttonDown(prevTrackPin);
buttonDown(nextTrackPin);
buttonDown(volumeUpPin);
buttonDown(volumeDownPin);
buttonDown(pausePin);

}

bool buttonDown(int pin) {
  Serial.print("Pin " + (String) pin + ": ");
  Serial.println(pin);
  return analogRead(pin) > 500;
}
