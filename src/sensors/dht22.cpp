#include "dht22.h"

void Dht22::setup() {
    dht.begin();
}

float Dht22::readHumidity() {
    return dht.readHumidity();
}

float Dht22::readTemperature() {
    return dht.readTemperature();
}

bool Dht22::verify(float result) {
    return isnan(result);
}