#include <Arduino.h>
#include <rf24g.h>
#include <ArduinoJson.h> //https://arduinojson.org/v6/example/parser/

class Transmit {

  private:
    RF24_G radio;
    int channel;
    int destination;
    StaticJsonDocument<200> jsonBuffer;
    bool active = false;
    bool dead = false;

  public:
    Transmit();
    Transmit(int _channel, int _destination);

    void begin();
    void receive();
    bool isActive();
    bool isDead();

    void sendRaw(String key, String value);
    void send(String key, String value);
    void send(String key, int value);
    void send(String key, float value);
};
