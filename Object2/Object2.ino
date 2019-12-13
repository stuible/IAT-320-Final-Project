// Object 2 (Portable Radio)

#include <ArduinoJson.h> // JSON Library: https://arduinojson.org/v6/example/parser/

#include "Transmit.h"

Transmit transmit;

int objectChannel = 3;
int baseChannel = 1;

const int volumePin = A0;
const int AMFMPin =  A1;

int prevVolume = 0;
bool prevAM;

void setup() {
  Serial.begin(9600);

  transmit = Transmit(objectChannel, baseChannel);

  prevAM = analogRead(AMFMPin) > 500 ? true : false;

}
void loop() {
  transmit.receive();

  int volume = analogRead(volumePin);
  bool AM = analogRead(AMFMPin) > 500 ? true : false;

  // Only tell the base about a volume change if it's changed more than 25
  if (abs(abs(prevVolume) - abs(volume)) > 25) {
    // passed threshold
    transmit.send("vol", (int) map(volume, 350, 1023, 100, 0));
    prevVolume = volume;
  }

  if (prevAM != AM) {
    transmit.send("AM", AM);
    prevAM = AM;
  }

}
