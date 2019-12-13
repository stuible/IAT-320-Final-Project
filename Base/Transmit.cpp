#include "Transmit.h"

// Initialize Constructor
Transmit::Transmit() {
//  Serial.println("Initialize");
}

// Instantiate Constructor
Transmit::Transmit(int _channel, int _destination, RF24_G _radio) {
  channel = _channel;
  destination = _destination;
  radio = _radio; // Connect CE to 9 and CSN to 10
}

void Transmit::sendRaw(String key, String value) {
//  Serial.print("/*");

  //30 character char array (Fixed packet size for Radio)
  char message[30] = "                              ";

  // Variable length message string
  String messageString = "{" + key + ": " + value + "}";

  // Load in the first 30 charactors of message that will be sent in the packet
  for (int i = 0; i < messageString.length(); i++) {
    message[i] = messageString[i];
  }

//  Serial.println(message);

  // create a variable to store the received number
  char recMessage[30];
  // declare the sender packet variable
  packet sender;
  // declare the receiver packet variable
  packet receiver;
  // set the destination of the packet to address 1
//  Serial.print("Seding here:");
//  Serial.println(destination);
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
//void Transmit::send(String key, bool value) {
//  sendRaw(key, value ? "true" : "false");
//}

void Transmit::update() {

}
