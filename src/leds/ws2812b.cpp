#include "ws2812b.h"

WS2812b::WS2812b() {
  // empty constructor
}

void WS2812b::setup() {
  FastLED.addLeds<CHIPSET, LED_PIN>(leds, NUM_LEDS); 
}

void WS2812b::loop() {
  for(int i; i < 24; i++) {
    leds[i] = CRGB::BlueViolet; FastLED.show(); delay(60);
    leds[i] = CRGB::Black; FastLED.show(); delay(60);
  }
}