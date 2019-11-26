#include <Arduino.h>
#include <rf24g.h>
#include "Transmit.h"

class Gadget {
  private:
    int detectorPin;
    int radioAddress;
    RF24_G radio;
    Transmit transmit;
    bool active = false;
    bool pickedUp = false;
    bool dead = false;


  public:
    Gadget();
    Gadget(int _radioAddress, int _detectorPin, RF24_G _radio);
    void gogo();
    bool isDetected();
    int getAddress();
    bool isActive();
    bool isActive(bool _active);
    bool isDead();
    bool isDead(bool _dead);
    bool isPickedUp();
    bool isPickedUp(bool _pickedUp);
    void send(String key, bool value);

};
