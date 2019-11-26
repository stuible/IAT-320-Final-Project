#include "Base.h"

int Base::getAddressFromIndex(int index) {
  int address = index + 2;
  return address;
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
