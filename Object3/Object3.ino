// Acc Libraries
#include <ArduinoJson.h> //https://arduinojson.org/v6/example/parser/
#include <Button.h>

#include "Transmit.h"

Transmit transmit;

int objectChannel = 4;
int baseChannel = 1;


Button prevTrack(3); //Correct
Button nextTrack(1); //Correct
Button volumeUp(12); //Correct
Button volumeDown(6); //Correct
Button pause(2); //Correct

//bool prevTrackPressed = false;
//bool nextTrackPressed =  false;
//bool volumeUpPressed = false;
//bool volumeDownPressed = false;
//bool pausePressed = false;

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


  //  else  Serial.println("Prev Track Button state the same");

  //  buttonDown(prevTrackPin);
  //buttonDown(nextTrackPin);
  //buttonDown(volumeUpPin);
  //buttonDown(volumeDownPin);
  //buttonDown(pausePin);

}

bool buttonDown(int pin) {
  //  Serial.print("Pin " + (String) pin + ": ");
  //  Serial.println(digitalRead(pin));
  return digitalRead(pin);
}
