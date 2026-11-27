// 06 — LED Light Meter (74HC595)
// LDR sensor → 8-LED bar graph through a shift register.
// Teaches: shiftOut(), bit patterns, driving 8 outputs on 3 pins,
// non-blocking sensor sampling.

const uint8_t DATA_PIN  = 2;   // 74HC595 DS  (pin 14)
const uint8_t CLOCK_PIN = 3;   // 74HC595 SHCP (pin 11)
const uint8_t LATCH_PIN = 4;   // 74HC595 STCP (pin 12)
const uint8_t LDR_PIN   = A0;  // light sensor module analog out

const unsigned long SAMPLE_MS = 100;   // sensor refresh rate
const uint8_t SAMPLES = 8;             // averaging to kill jitter

// 595 outputs: bit0 = Q0 = leftmost LED.
void writeLeds(uint8_t pattern) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, pattern);
  digitalWrite(LATCH_PIN, HIGH);
}

// level 0..8 → bar-graph pattern (1,3,7,15,…,255)
uint8_t barPattern(uint8_t level) {
  return level == 0 ? 0 : (uint8_t)((1 << level) - 1);
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Light meter — cover/shine the LDR");
  writeLeds(0);
}

void loop() {
  static unsigned long lastSample = 0;
  if (millis() - lastSample < SAMPLE_MS) return;   // non-blocking rate limit
  lastSample = millis();

  long sum = 0;
  for (uint8_t i = 0; i < SAMPLES; i++) sum += analogRead(LDR_PIN);
  int light = sum / SAMPLES;                       // 0..1023

  // Map light → 0..8 LEDs. Adjust CAL_LOW/CAL_HIGH to your room if needed.
  const int CAL_LOW = 80, CAL_HIGH = 900;
  uint8_t level = constrain(map(light, CAL_LOW, CAL_HIGH, 0, 8), 0, 8);
  writeLeds(barPattern(level));

  Serial.print("light="); Serial.print(light);
  Serial.print("  level="); Serial.println(level);
}
