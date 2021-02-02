#include "MHZ19.h"
#include <SoftwareSerial.h>

#define RX_PIN 33
#define TX_PIN 32

MHZ19 mhz19;

SoftwareSerial mySerial(RX_PIN, TX_PIN);

class Mhz19b {
public:
    Mhz19b();
    void setup();
    int readCO2();
    boolean verify(int result);
}