// Object 1 (Old School Radio)

#include <ArduinoJson.h> // JSON Library: https://arduinojson.org/v6/example/parser/

#include "Transmit.h"

Transmit transmit;

int objectChannel = 2;
int baseChannel = 1;

const int volumePin = A0;

int prevVolume = 0;


void setup() {
  Serial.begin(9600);

  transmit = Transmit(objectChannel, baseChannel);


}
void loop() {
  transmit.receive();


  int volume = analogRead(volumePin);

  // Only tell the base about a volume change if it's changed more than 25
  if (abs(abs(prevVolume) - abs(volume)) > 25) {
    transmit.send("vol", (int) map(volume, 0, 1023, 100, 0));
    prevVolume = volume;
  }

}
