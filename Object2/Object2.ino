// Acc Libraries
#include <ArduinoJson.h> //https://arduinojson.org/v6/example/parser/

#include "Transmit.h"

Transmit transmit;

int objectChannel = 3;
int baseChannel = 1;

const int volumePin = A0;
const int AMFMPin =  A1;

int prevVolume = 0;
bool prevAM;

//350 - 1023

void setup() {
  Serial.begin(9600);

  transmit = Transmit(objectChannel, baseChannel);

  prevAM = analogRead(AMFMPin) > 500 ? true : false;

}
void loop() {
  transmit.receive();

  //  transmit.send("track", "next");

  int volume = analogRead(volumePin);
  bool AM = analogRead(AMFMPin) > 500 ? true : false;

  if (abs(abs(prevVolume) - abs(volume)) > 25) {
    //    Serial.println("cahnged enough");
    transmit.send("vol", (int) map(volume, 350, 1023, 0, 100));
    prevVolume = volume;
  }

  if (prevAM != AM) {
    transmit.send("AM", AM);
    prevAM = AM;
  }


  //  Serial.print("volume: ");
  //  Serial.println(volume);

  //    Serial.print("AM / FM: ");
  //    Serial.println(AMFM);

}
