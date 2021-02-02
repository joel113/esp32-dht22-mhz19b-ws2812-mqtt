#include "DHT.h"

#define DHTTYPE DHT22
#define DHTPIN 4

class Dht22 {
    DHT dht;
public:
    Dht22() : dht(DHTPIN, DHT22) {};
    void setup();
    float readHumidity();
    float readTemperature();
    bool verify(float result);
};