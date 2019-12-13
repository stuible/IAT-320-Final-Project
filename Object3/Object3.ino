// Object 3 (MP3 Player)

#include <ArduinoJson.h> // JSON Library: https://arduinojson.org/v6/example/parser/
#include <Button.h> // Nice little library that handles debouncing (https://github.com/madleech/Button)

#include "Transmit.h"

Transmit transmit;

int objectChannel = 4;
int baseChannel = 1;

// Button objects of the 4 buttons
Button prevTrack(3);
Button nextTrack(1);
Button volumeUp(12);
Button volumeDown(6);
Button pause(2);


void setup() {
  Serial.begin(9600);

  prevTrack.begin();
  nextTrack.begin();
  volumeUp.begin();
  volumeDown.begin();
  pause.begin();

  transmit = Transmit(objectChannel, baseChannel);

}
void loop() {
  transmit.receive();

  //  transmit.send("track", "next");

  if (prevTrack.pressed()) {
    //    Serial.println("Prev Pressed");
    transmit.send("track", "prev");
  }
  if (nextTrack.pressed()) {
    //    Serial.println("Next Pressed");
    transmit.send("track", "next");
  }
  if (volumeUp.pressed()) {
    //    Serial.println("Vol Up Pressed");
    transmit.send("vol", "up");
  }
  if (volumeDown.pressed()) {
    //    Serial.println("Vol Down Pressed");
    transmit.send("vol", "down");
  }
  if (pause.pressed()) {
    //    Serial.println("Pauses Pressed");
    transmit.send("track", "pause");
  }

}
