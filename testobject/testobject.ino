// Acc Libraries
#include <Wire.h>
#include <ArduinoJson.h> //https://arduinojson.org/v6/example/parser/

#include "Transmit.h"



int objectChannel = 5;
int baseChannel = 1;

Transmit transmit;

void setup() {
  Serial.begin(9600);
  transmit = Transmit(objectChannel, baseChannel);

}
void loop() {
    Serial.println("running loop");
    transmit.send("test", "hehe");

    delay(1000);

}
