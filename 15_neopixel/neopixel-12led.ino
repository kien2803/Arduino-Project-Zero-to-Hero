// 15 - NeoPixel 12 LED RGB Ring / Module
// Simple color wipe and rainbow effects

#include <Adafruit_NeoPixel.h>

#define PIN        6
#define NUMPIXELS  12

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(50);  // 0-255, keep moderate to avoid high current
  pixels.clear();
  pixels.show();
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}

void loop() {
  colorWipe(pixels.Color(255, 0, 0), 50);   // Red
  colorWipe(pixels.Color(0, 255, 0), 50);   // Green
  colorWipe(pixels.Color(0, 0, 255), 50);   // Blue
  colorWipe(pixels.Color(0, 0, 0), 30);     // Off
  delay(500);
}
