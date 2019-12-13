#include "Base.h"

void Base::begin() {
  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

}

int Base::getAddressFromIndex(int index) {
  int address = index + 2;
  return address;
}

void Base::update() {
//  No behavior needed
}

void Base::startSetLED() {
  strip.clear();  
}
void Base::endSetLED() {
  strip.show();
}

void Base::sendToComputerRaw(String key, String value) {
  Serial.print("{" + key + ": " + value +  "}\n");
}
void Base::sendToComputer(String key, String value) {
  sendToComputerRaw(key, "\"" + value + "\"");
}
void Base::sendToComputer(String key, int value) {
  sendToComputerRaw(key, (String) value);
}
void Base::sendToComputer(String key, bool value) {
  sendToComputerRaw(key, (String) value);
}

void Base::setLEDcolour(int startLED, int endLED, uint32_t color) {
  for (int i = startLED; i <= endLED; i++) {
    strip.setPixelColor(i, color); // Set pixel 'c' to value 'color'
  }
}
