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
    bool ready = false;
    bool pickedUp = false;
    bool dead = false;
    int LEDstartIndex;
    int LEDendIndex;


  public:
    Gadget();
    Gadget(int _radioAddress, int _detectorPin, int _LEDstartIndex, int _LEDendIndex, RF24_G _radio);
    void gogo();
    bool isDetected();
    int getAddress();
    bool isActive();
    bool isActive(bool _active);
    bool isReady();
    bool isReady(bool _ready);
    bool isDead();
    bool isDead(bool _dead);
    bool isPickedUp();
    bool isPickedUp(bool _pickedUp);
    void send(String key, bool value);
    int getLEDstart();
    int getLEDend();

};
