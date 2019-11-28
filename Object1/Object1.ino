// Acc Libraries
#include <ArduinoJson.h> //https://arduinojson.org/v6/example/parser/

#include "Transmit.h"

Transmit transmit;

int objectChannel = 2;
int baseChannel = 1;

const int volumePin = A0;

int prevVolume = 0;

//0 - 1020

void setup() {
  Serial.begin(9600);

//  transmit = Transmit(objectChannel, baseChannel);


}
void loop() {
//  transmit.receive();

  //  transmit.send("track", "next");

  int volume = analogRead(volumePin);

  if (abs(abs(prevVolume) - abs(volume)) > 25) {
    //    Serial.println("cahnged enough");
//    transmit.send("vol", (int) map(volume, 350, 1023, 0, 100));
    prevVolume = volume;
  }

    Serial.print("volume: ");
    Serial.println(volume);

  //    Serial.print("AM / FM: ");
  //    Serial.println(AMFM);

}
