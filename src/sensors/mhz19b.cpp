#include "mhz19b.h"

void Mhz19b::setup() {
    mySerial.begin(9600);
    mhz19.begin(mySerial);
}

int Mhz19b::readCO2() {
    return mhz19.getCO2();
}

boolean Mhz19b::verify() {
    return mhz19.errorCode != RESULT_OK;
}