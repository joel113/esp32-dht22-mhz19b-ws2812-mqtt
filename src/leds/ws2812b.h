#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    24

class WS2812b {
    CRGB leds[NUM_LEDS];
public:
    WS2812b();
    void setup();
    void loop();
};