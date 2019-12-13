#include <Arduino.h>
#include <rf24g.h>

class Transmit {

  private:
    RF24_G radio;
    int channel;
    int destination;

  public:
    Transmit();
    Transmit(int _channel, int _destination, RF24_G radio);

    void begin();
    void update();

    void sendRaw(String key, String value);
    void send(String key, String value);
    void send(String key, int value);
    void send(String key, float value);
//    void send(String key, bool value);
};
