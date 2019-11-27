// Acc Libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <ArduinoJson.h> //https://arduinojson.org/v6/example/parser/

#include "Transmit.h"
#include "Display.h" // Custom Display class

int objectChannel = 5;
int baseChannel = 1;

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

// Global Acc X and Y Variables
float prevX = 0;
float prevY = 0;

bool completedActionY = false;

Transmit transmit;
Display display;

void setup() {
  Serial.begin(9600);
  display.begin();
  transmit = Transmit(objectChannel, baseChannel);
  // print out the details of the radio's configuration (useful for debug)
  // Initialise the acc sensor
  if (!accel.begin())
  {
    Serial.println("Acc Error");
    while (1)
      ;
  }
}
void loop() {
  transmit.receive();
  display.update();

  // If active turn display on, if not, turn off
  if (transmit.isActive())
    display.on();
  else
    display.off();

  // Get a new acc sensor event
  sensors_event_t event;
  accel.getEvent(&event);

  float currX = event.acceleration.x;
  float currY = event.acceleration.y;

  // If current Y acceleration has crossed "5" for the first time, next song
  if (currY >= 5 && prevY < 5)
  {
    // Only register action if this is the first gesture recognized
    if (!completedActionY) transmit.send("track", "next");
    // Set action as already complete
    completedActionY = true;
  }

  // If current Y acceleration has crossed "-5" for the first time, previous song
  if (currY >= -5 && prevY < -5)
  {
    // Only register action if this is the first gesture recognized
    if (!completedActionY) transmit.send("track", "previous");
    // Set action as already complete
    completedActionY = true;
  }

  // When Y motion is finished, reset boolean
  if (currY < 1 && currY > -1) completedActionY = false;


  // If the force in X has cahnged by more than 0.2, update the volume
  if (abs(abs(prevX) - abs(currX)) > 0.2)
  {

    // Map X Axis of Acc to "Volume", multiple and then divide by 100 for more refined map
    float volume = map(currX * 100, -8 * 100, 2 * 100, 0 * 100, 100 * 100) / 100;
    transmit.send("vol", volume);
    display.setVolume(volume);
  }
  //    delay(100);

  prevX = currX;
  prevY = currY;
}
