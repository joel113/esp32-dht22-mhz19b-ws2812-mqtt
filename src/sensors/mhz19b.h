#include "MHZ19.h"
#include <SoftwareSerial.h>

#define RX_PIN 33
#define TX_PIN 32

class Mhz19b {
    MHZ19 mhz19;
    SoftwareSerial mySerial;
public:
    Mhz19b() : mySerial(RX_PIN, TX_PIN) {};
    void setup();
    int readCO2();
    boolean verify();
};