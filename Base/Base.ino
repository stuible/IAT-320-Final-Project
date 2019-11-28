#include <rf24g.h>
#include <Adafruit_NeoPixel.h>

#include "Gadget.h"
#include "Base.h"

Adafruit_NeoPixel strip;

Base base;
RF24_G radio;

const int BASE_RADIO_CHANNEL = 1;

const int OBJECT_COUNT = 4;
Gadget objects[OBJECT_COUNT];

const int OLD_SCHOOL_RADIO_INDEX = 0;
const int PORTABLE_RADIO_INDEX = 1;
const int MP3_PLAYER_INDEX = 2;
const int PHONE_INDEX = 3;

//int activeObjectIndex = -1;
int activeObjectIndex = -1;

uint32_t green = strip.Color(0, 200, 0);
uint32_t yellow = strip.Color(200, 200, 0);
uint32_t red = strip.Color(200, 0, 0);


void setup() {

  base.begin();

  // create the RF24G object with an address of 4, using pins 7 and 8
  radio = RF24_G(BASE_RADIO_CHANNEL, 9, 10);

  // Instantiate Objects
  objects[0] = Gadget(base.getAddressFromIndex(OLD_SCHOOL_RADIO_INDEX), A0, 0, 9, radio);  // Old School Radio
  objects[1] = Gadget(base.getAddressFromIndex(PORTABLE_RADIO_INDEX), A1, 10, 19, radio);  // Portable Radio
  objects[2] = Gadget(base.getAddressFromIndex(MP3_PLAYER_INDEX), A2, 20, 29, radio);  // MP3 Player
  objects[3] = Gadget(base.getAddressFromIndex(PHONE_INDEX), A3, 30, 39, radio);   // Phone

  Serial.begin(9600);

  if (activeObjectIndex != -1) objects[activeObjectIndex].isActive(true);
  objects[activeObjectIndex + 1].isReady(true);
  base.sendToComputer("activeObject", activeObjectIndex);

  setColours();

//  base.startSetLED();
//  base.setLEDcolour(objects[OLD_SCHOOL_RADIO_INDEX].getLEDstart(), objects[OLD_SCHOOL_RADIO_INDEX].getLEDend(), green);
//  base.setLEDcolour(objects[PORTABLE_RADIO_INDEX].getLEDstart(), objects[PORTABLE_RADIO_INDEX].getLEDend(), yellow);
//  base.endSetLED();
}

void loop() {
  //  delay(2000);
  //  base.startSetLED();
  //  base.setLEDcolour(objects[OLD_SCHOOL_RADIO_INDEX].getLEDstart(), objects[OLD_SCHOOL_RADIO_INDEX].getLEDend(), yellow);
  //  base.setLEDcolour(objects[PORTABLE_RADIO_INDEX].getLEDstart(), objects[PORTABLE_RADIO_INDEX].getLEDend(), green);
  //  base.endSetLED();
  //  delay(2000);
  //  base.startSetLED();
  //  base.setLEDcolour(objects[OLD_SCHOOL_RADIO_INDEX].getLEDstart(), objects[OLD_SCHOOL_RADIO_INDEX].getLEDend(), green);
  //  base.setLEDcolour(objects[PORTABLE_RADIO_INDEX].getLEDstart(), objects[PORTABLE_RADIO_INDEX].getLEDend(), yellow);
  //  base.endSetLED();
  //   delay(2000);
  //  base.startSetLED();
  //  base.setLEDcolour(objects[OLD_SCHOOL_RADIO_INDEX].getLEDstart(), objects[OLD_SCHOOL_RADIO_INDEX].getLEDend(), yellow);
  //  base.setLEDcolour(objects[PORTABLE_RADIO_INDEX].getLEDstart(), objects[PORTABLE_RADIO_INDEX].getLEDend(), green);
  //  base.endSetLED();
  //  delay(2000);
  //  base.startSetLED();
  //  base.setLEDcolour(objects[OLD_SCHOOL_RADIO_INDEX].getLEDstart(), objects[OLD_SCHOOL_RADIO_INDEX].getLEDend(), green);
  //  base.setLEDcolour(objects[PORTABLE_RADIO_INDEX].getLEDstart(), objects[PORTABLE_RADIO_INDEX].getLEDend(), yellow);
  //  base.endSetLED();

  int nextObjectIndex = activeObjectIndex + 1;

  //  Serial.println("");Serial.println("");Serial.println("");Serial.println("");Serial.println("");Serial.println("");
//    Serial.println("----------------------");
//    Serial.println("activeObjectIndex: " + (String)activeObjectIndex);
//    Serial.println(objects[activeObjectIndex].isDetected());
//    Serial.println(objects[activeObjectIndex].isActive());
//    Serial.println(objects[activeObjectIndex].isPickedUp());
//    Serial.println("----------------------");

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
    Serial.println("Active Object Picked Up");
    objects[activeObjectIndex].isPickedUp(true);
    objects[nextObjectIndex].isReady(true);
    setColours();


  }

  // Check of there is another object
  if (nextObjectIndex < OBJECT_COUNT) {

    // Detect if Next object has been picked up
    if (!objects[nextObjectIndex].isDetected()) {
      //      Serial.println("Next Object Picked Up");
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



  //  delay(1000);

  //  base.setLEDcolour(objects[activeObjectIndex + 1].getLEDstart(), objects[activeObjectIndex + 1].getLEDend(), yellow);

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

void setColours() {
  Serial.println("about to start set colours");
  base.startSetLED();
  Serial.println("about to start set colours 2");
  for (int i = 0; i < OBJECT_COUNT; i++) {
    if (objects[i].isDead()) base.setLEDcolour(objects[i].getLEDstart(), objects[i].getLEDend(), red);
    else if (objects[i].isActive()) base.setLEDcolour(objects[i].getLEDstart(), objects[i].getLEDend(), yellow);
    else if (objects[i].isReady()) base.setLEDcolour(objects[i].getLEDstart(), objects[i].getLEDend(), green);
          

    Serial.println("---- OBJECT " + (String) i + "----");
    Serial.print("start: ");
    Serial.println(objects[i].getLEDstart());
    Serial.print("end: ");
    Serial.println(objects[i].getLEDend());
    Serial.print("dead: ");
    Serial.println(objects[i].isDead());
    Serial.print("ready: ");
    Serial.println(objects[i].isReady());
    Serial.print("active: ");
    Serial.println(objects[i].isActive());
    Serial.print("picked up: ");
    Serial.println(objects[i].isPickedUp());

    delay(50);
  }
  Serial.println("about to start set colours 3");
  base.endSetLED();
  delay(100);
  Serial.println("about to start set colours 4");
}
