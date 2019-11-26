#include <rf24g.h>
#include "Gadget.h"
#include "Base.h"

Base base;
RF24_G radio;

const int BASE_RADIO_CHANNEL = 1;

const int OBJECT_COUNT = 4;
Gadget objects[OBJECT_COUNT];

const int OLD_SCHOOL_RADIO_INDEX = 0;
const int PORTABLE_RADIO_INDEX = 1;
const int MP3_PLAYER_INDEX = 2;
const int PHONE_INDEX = 3;

int activeObjectIndex = 3;


void setup() {
  Serial.begin(9600);
  // create the RF24G object with an address of 4, using pins 7 and 8
  radio = RF24_G(BASE_RADIO_CHANNEL, 9, 10);

  // Instantiate Objects
  objects[0] = Gadget(base.getAddressFromIndex(OLD_SCHOOL_RADIO_INDEX), A0, radio);  // Old School Radio
  objects[1] = Gadget(base.getAddressFromIndex(PORTABLE_RADIO_INDEX), A1, radio);  // Portable Radio
  objects[2] = Gadget(base.getAddressFromIndex(MP3_PLAYER_INDEX), A2, radio);  // MP3 Player
  objects[3] = Gadget(base.getAddressFromIndex(PHONE_INDEX), A3, radio);   // Phone

  objects[activeObjectIndex].isActive(true);
  base.sendToComputer("activeObject", activeObjectIndex);
}

void loop() {
  int nextObjectIndex = activeObjectIndex + 1;
  
//  Serial.println("");Serial.println("");Serial.println("");Serial.println("");Serial.println("");Serial.println("");
//  Serial.println("----------------------");
//  Serial.println("activeObjectIndex: " + (String)activeObjectIndex);
//  Serial.println(objects[activeObjectIndex].isDetected());
//  Serial.println(objects[activeObjectIndex].active);
//  Serial.println(objects[activeObjectIndex].pickedUp);
//  Serial.println("----------------------");

  // Detect if Active object has been put down
  if (objects[activeObjectIndex].isDetected()
      && objects[activeObjectIndex].isActive()
      && objects[activeObjectIndex].isPickedUp())
  {
//    Serial.println("Active Object Put Down");
    objects[activeObjectIndex].isPickedUp(false);
  }
  // Detect if Active object has been picked up
  else if (!objects[activeObjectIndex].isDetected() && !objects[activeObjectIndex].isPickedUp()) {
//    Serial.println("Active Object Picked Up");
    objects[activeObjectIndex].isPickedUp(true);
  }

  // Check of there is another object
  if (nextObjectIndex < OBJECT_COUNT) {

    // Detect if Next object has been picked up
    if (!objects[nextObjectIndex].isDetected()) {
//      Serial.println("Next Object Picked Up");
      objects[activeObjectIndex].isActive(false);

      objects[nextObjectIndex].isActive(true);
      objects[nextObjectIndex].isPickedUp(true);

      activeObjectIndex++;

      
      base.sendToComputer("activeObject", activeObjectIndex);
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
//        Serial.println("Message from Oldschool Radio");
      }
      else if (receiver.getAddress() == objects[PORTABLE_RADIO_INDEX].getAddress()) {
//        Serial.println("Message from Portable Radio");
      }
      else if (receiver.getAddress() == objects[MP3_PLAYER_INDEX].getAddress()) {
//        Serial.println("Message from MP3 Player");
      }
      else if (receiver.getAddress() == objects[PHONE_INDEX].getAddress()) {
//        Serial.println("Message from Phone");

      }


      // load the payload into the payload string
      receiver.readPayload(payload, 30);
      // print the payload
      //    Serial.print("payload: ");
      Serial.print((String) payload + "\n");
    }
//    else  Serial.println("Message from Non Active Device, Ignored");


    // since the address in the packet object is already
    // set to the address of the receiver, it doesn't need to be changed
    // hence, we can write the packet back to the receiver
    // we may check to see if the transmission failed, if so we just drop the packet
    //    if (radio.write(&receiver) == false) {
    //      Serial.println("transmit back failed!");
    //      Serial.println("dropping packet...");
    //    }
  }

  delay(50);
}
