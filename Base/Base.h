#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Helper functions for Base

class Base {
  private:
    const int LED_PIN = 3;
    const int LED_COUNT = 59;
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

  public:
    //    Base();
    void begin();
    void update();
    void Base::startSetLED();
    void Base::endSetLED();
    int getAddressFromIndex(int index);
    void sendToComputerRaw(String key, String value);
    void sendToComputer(String key, String value);
    void sendToComputer(String key, int value);
    void sendToComputer(String key, bool value);

    void setLEDcolour(int startLED, int endLED, uint32_t color);
};
