#include <Arduino.h>

// Helper functions for Base

class Base {
  private:

  public:
//    Gadget(int _radioAddress, int _detectorPin);
    int getAddressFromIndex(int index);
    void sendToComputerRaw(String key, String value);
    void sendToComputer(String key, String value);
    void sendToComputer(String key, int value);
    void sendToComputer(String key, bool value);
};
