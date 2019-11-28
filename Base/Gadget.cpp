#include "Gadget.h"

// Constructor
Gadget::Gadget() {}

// Constructor
Gadget::Gadget(int _radioAddress, int _detectorPin, int _LEDstartIndex, int _LEDendIndex, RF24_G _radio) {
  detectorPin = _detectorPin;
  radioAddress = _radioAddress;
  radio = _radio;
  LEDstartIndex = _LEDstartIndex;
  LEDendIndex = _LEDendIndex;
  transmit = Transmit(1, _radioAddress, _radio);
}

bool Gadget::isDetected() {
  int detectorVoltage = analogRead(detectorPin);
  //  Serial.print("Analog reading = ");
  //  Serial.println(detectorVoltage);

  return detectorVoltage > 500;
}

// Loop function specially named for this class ;)
void Gadget::gogo() {

}

void Gadget::send(String key, bool value) {
  transmit.send(key, value ? "true" : "false");
}

int Gadget::getAddress() {
  return radioAddress;
}

bool Gadget::isReady() {
  return ready;
}

bool Gadget::isReady(bool _ready) {
  ready = _ready;
  return isActive();
}

bool Gadget::isActive() {
  return active;
}

bool Gadget::isActive(bool _active) {
  active = _active;
  //  Serial.println("About to send active state over radio back to object");
  send("active", _active);
  return isActive();
}

bool Gadget::isDead() {
  return dead;
}

bool Gadget::isDead(bool _dead) {
  dead = _dead;
  send("dead", _dead);
  return isDead();
}

bool Gadget::isPickedUp() {
  return pickedUp;
}

bool Gadget::isPickedUp(bool _pickedUp) {
  pickedUp = _pickedUp;
  return isPickedUp();
}

int Gadget::getLEDstart() {
  return LEDstartIndex;
}
int Gadget::getLEDend() {
  return LEDendIndex;
}
