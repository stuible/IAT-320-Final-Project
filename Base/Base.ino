#include <rf24g.h>
#include <Adafruit_NeoPixel.h>

#include "Gadget.h"
#include "Base.h"

Adafruit_NeoPixel strip;

// LED Ranges:
// object1: 24 (0-23) object2: 13 (24-37) object3: 15 (38-52) object4: 17 (53-69)

Base base;
RF24_G radio;

const int BASE_RADIO_CHANNEL = 1;

const int OBJECT_COUNT = 4;
Gadget objects[OBJECT_COUNT];

const int OLD_SCHOOL_RADIO_INDEX = 0;
const int PORTABLE_RADIO_INDEX = 1;
const int MP3_PLAYER_INDEX = 2;
const int PHONE_INDEX = 3;

int activeObjectIndex = -1;

uint32_t green = strip.Color(0, 200, 0);
uint32_t yellow = strip.Color(200, 200, 0);
uint32_t red = strip.Color(200, 0, 0);


void setup() {

  base.begin();

  // create the RF24G object with an address of 4, using pins 7 and 8
  radio = RF24_G(BASE_RADIO_CHANNEL, 9, 10);

  // Instantiate Objects
  objects[0] = Gadget(base.getAddressFromIndex(OLD_SCHOOL_RADIO_INDEX), A0, 0, 23, radio);  // Old School Radio
  objects[1] = Gadget(base.getAddressFromIndex(PORTABLE_RADIO_INDEX), A1, 24, 34, radio);  // Portable Radio
  objects[2] = Gadget(base.getAddressFromIndex(MP3_PLAYER_INDEX), A2, 35, 44, radio);  // MP3 Player
  objects[3] = Gadget(base.getAddressFromIndex(PHONE_INDEX), A3, 51, 58, radio);   // Phone

  Serial.begin(9600);

  if (activeObjectIndex != -1) objects[activeObjectIndex].isActive(true);
  objects[activeObjectIndex + 1].isReady(true);
  base.sendToComputer("activeObject", activeObjectIndex);

  setColours();

}

void loop() {

  int nextObjectIndex = activeObjectIndex + 1;

  // Detect if Active object has been put down
  if (objects[activeObjectIndex].isDetected()
      && objects[activeObjectIndex].isActive()
      && objects[activeObjectIndex].isPickedUp())
  {
    //    Serial.println("Active Object Put Down");
    objects[activeObjectIndex].isPickedUp(false);
    setColours();
  }
  // Detect if Active object has been picked up
  else if (!objects[activeObjectIndex].isDetected() && !objects[activeObjectIndex].isPickedUp()) {
  // Active Object Picked Up
    objects[activeObjectIndex].isPickedUp(true);
    objects[nextObjectIndex].isReady(true);
    setColours();


  }

  // Check of there is another object
  if (nextObjectIndex < OBJECT_COUNT) {

    // Detect if Next object has been picked up
    if (!objects[nextObjectIndex].isDetected()) {
      // Next Object Picked Up
      objects[activeObjectIndex].isActive(false);
      objects[activeObjectIndex].isDead(true);

      objects[nextObjectIndex].isActive(true);
      objects[nextObjectIndex].isReady(false);
      objects[nextObjectIndex].isPickedUp(true);

      activeObjectIndex++;

      objects[activeObjectIndex + 1].isReady(true);

      base.sendToComputer("activeObject", activeObjectIndex);
      setColours();
    }

  }

  // declare packet variable
  packet receiver;
  // declare string to place the packet payload in
  char payload[30] = "                              ";
  // check if the radio has any packets in the receive queue
  if (radio.available() == true) {
    //    Serial.println("packet received!");
    // read the data into the packet
    radio.read(&receiver);

    // Check the source address of the received packet
    if (receiver.getAddress() == base.getAddressFromIndex(activeObjectIndex)) {

      if (receiver.getAddress() == objects[OLD_SCHOOL_RADIO_INDEX].getAddress()) {
        // Message from Oldschool Radio
      }
      else if (receiver.getAddress() == objects[PORTABLE_RADIO_INDEX].getAddress()) {
        // Message from Portable Radio
      }
      else if (receiver.getAddress() == objects[MP3_PLAYER_INDEX].getAddress()) {
        // Message from MP3 Player
      }
      else if (receiver.getAddress() == objects[PHONE_INDEX].getAddress()) {
        // Message from Phone

      }


      // load the payload into the payload string
      receiver.readPayload(payload, 30);
      // print the payload
      Serial.print((String) payload + "\n");
    }
  }

  delay(50);
}

void setColours() {

  base.startSetLED();
  for (int i = 0; i < OBJECT_COUNT; i++) {
    if (objects[i].isDead()) base.setLEDcolour(objects[i].getLEDstart(), objects[i].getLEDend(), red);
    else if (objects[i].isActive()) base.setLEDcolour(objects[i].getLEDstart(), objects[i].getLEDend(), yellow);
    else if (objects[i].isReady()) base.setLEDcolour(objects[i].getLEDstart(), objects[i].getLEDend(), green);


    delay(50);
  }
  base.endSetLED();
  delay(100);
}
