#include "Transmit.h"

// Initialize Constructor
Transmit::Transmit() {
  Serial.println("Initialize");
}

// Instantiate Constructor
Transmit::Transmit(int _channel, int _destination) {
  channel = _channel;
  destination = _destination;
  radio = RF24_G(channel, 9, 10); // Connect CE to 9 and CSN to 10
}

void Transmit::sendRaw(String key, String value) {

  //30 character char array (Fixed packet size for Radio)
  char message[30] = "                              ";

  // Variable length message string
  String messageString = "{" + key + ": " + value + "}";

  // Load in the first 30 charactors of message that will be sent in the packet
  for (int i = 0; i < messageString.length(); i++) {
    message[i] = messageString[i];
  }

  Serial.println(message);

  // create a variable to store the received number
  char recMessage[30];
  // declare the sender packet variable
  packet sender;
  // declare the receiver packet variable
  packet receiver;
  // set the destination of the packet to address 1
  sender.setAddress(destination);
  // write the payload to the packet
  sender.addPayload(message, 30);
  // print out the original payload
  // send the packet, if it is successful try to read back the packet
  if (radio.write(&sender) == true) {}
}

void Transmit::send(String key, String value) {
  sendRaw(key, "\"" + value + "\"");
}
void Transmit::send(String key, int value) {
  sendRaw(key, (String) value);
}
void Transmit::send(String key, float value) {
  sendRaw(key, (String) value);
}
void Transmit::send(String key, bool value) {
  sendRaw(key, value ? "true" : "false");
}

void Transmit::receive() {
  // declare packet variable
  packet receiver;
  // declare string to place the packet payload in
  char payload[30];
  // check if the radio has any packets in the receive queue
  if (radio.available() == true) {
    //    Serial.println("packet received!");
    // read the data into the packet
    radio.read(&receiver);


    // load the payload into the payload string
    receiver.readPayload(payload, 30);
    // print the payload

    Serial.print("payload: ");
    Serial.println(payload);

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(jsonBuffer, payload);

    // Test if parsing succeeds.
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
    }
    else
    {

      //      // check to see if the platform thinks this object should be active
      String activeJSON = jsonBuffer["active"];

      if (activeJSON == "true") active = true;
      else if (activeJSON == "false") active = false;

      Serial.print("Active: ");
      Serial.println(active);

      String deadJSON = jsonBuffer["dead"];
      if (deadJSON == "true") dead = true;
      else if (deadJSON == "false") dead = false;

      Serial.print("Dead: ");
      Serial.println(dead);
      //
      //      bool dead = jsonBuffer["dead"];
      //      Serial.print("Dead: ");
      //      Serial.println(dead);
    }

  }
}

bool Transmit::isActive() {
  return active;
}
bool Transmit::isDead() {
  return dead;
}
