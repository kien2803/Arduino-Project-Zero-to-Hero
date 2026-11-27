// 07 — Remote NeoPixel Lamp
// IR remote controls a 12-LED WS2812 ring: colors, brightness, effects.
// Teaches: IRremote v4 + repeat-frame filtering (same trap as the old
// relay lesson), Adafruit_NeoPixel, non-blocking animation.

#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

const uint8_t IR_PIN   = 11;   // 1838T receiver OUT
const uint8_t RING_PIN = 6;    // NeoPixel DIN (through ~220Ω)
const uint8_t NUM_LEDS = 12;

Adafruit_NeoPixel ring(NUM_LEDS, RING_PIN, NEO_GRB + NEO_KHZ800);

// ---- edit these after reading your remote's codes on Serial ----
// Upload → press buttons → Serial prints `command=0xNN` → fill in.
uint8_t CMD_POWER   = 0x45;   // toggle lamp
uint8_t CMD_COLOR   = 0x09;   // next color
uint8_t CMD_EFFECT  = 0x07;   // next effect (solid / rainbow spin)
uint8_t CMD_BRIGHT  = 0x15;   // brightness step up
// -------------------------------------------------------------

const uint32_t PALETTE[] = {
  Adafruit_NeoPixel::Color(255, 255, 255),   // warm white
  Adafruit_NeoPixel::Color(255, 60, 0),      // candle orange
  Adafruit_NeoPixel::Color(0, 120, 255),     // cool blue
  Adafruit_NeoPixel::Color(0, 255, 80),      // green
  Adafruit_NeoPixel::Color(180, 0, 255)      // violet
};
const uint8_t N_COLORS = sizeof(PALETTE) / sizeof(PALETTE[0]);
const uint8_t BRIGHT_STEPS[] = {20, 60, 120, 200, 255};
const uint8_t N_BRIGHT = sizeof(BRIGHT_STEPS);

bool lampOn = true;
uint8_t colorIx = 0, brightIx = 2, effect = 0;   // 0=solid, 1=spin
unsigned long lastStep = 0;
uint8_t spinPos = 0;

void render() {
  if (!lampOn) { ring.clear(); ring.show(); return; }
  if (effect == 0) {
    ring.fill(PALETTE[colorIx]);
  } else {                                      // rainbow chase
    for (uint8_t i = 0; i < NUM_LEDS; i++)
      ring.setPixelColor(i, ring.ColorHSV((i + spinPos) * 65536 / NUM_LEDS, 255, 120));
  }
  ring.show();
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  ring.begin();
  ring.setBrightness(BRIGHT_STEPS[brightIx]);
  render();
  Serial.println("NeoPixel lamp — press remote buttons to see their codes");
}

void loop() {
  if (IrReceiver.decode()) {
    auto &d = IrReceiver.decodedIRData;
    bool repeat = d.flags & IRDATA_FLAGS_IS_REPEAT;  // held-button frames
    if (!repeat) {
      Serial.print("protocol="); Serial.print(d.protocol);
      Serial.print(" command=0x"); Serial.println(d.command, HEX);
      if      (d.command == CMD_POWER)  lampOn = !lampOn;
      else if (d.command == CMD_COLOR && lampOn)  colorIx = (colorIx + 1) % N_COLORS;
      else if (d.command == CMD_EFFECT && lampOn) effect = (effect + 1) % 2;
      else if (d.command == CMD_BRIGHT && lampOn) {
        brightIx = (brightIx + 1) % N_BRIGHT;
        ring.setBrightness(BRIGHT_STEPS[brightIx]);
      }
      render();
    }
    IrReceiver.resume();
  }

  // non-blocking spin animation
  if (lampOn && effect == 1 && millis() - lastStep > 80) {
    lastStep = millis();
    spinPos++;
    render();
  }
}
