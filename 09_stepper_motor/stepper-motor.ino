// 09 — Stepper Motor (28BYJ-48 + ULN2003)
// A stepper moves in discrete steps — you energize coils in sequence.
// Pot sets speed, button reverses direction.
// Teaches: coil drive sequencing, why steppers ≠ DC motors,
// non-blocking step timing.

// ULN2003 inputs IN1..IN4 → D8..D11 (coils A,B,C,D)
const uint8_t COIL_PINS[4] = {8, 9, 10, 11};
const uint8_t BTN_DIR  = 2;     // press → reverse direction
const uint8_t POT_PIN  = A0;    // speed control

const unsigned long DEBOUNCE = 40;
const uint16_t STEP_MIN_US = 900;    // fastest  (~1.1 ms/step)
const uint16_t STEP_MAX_US = 20000;  // slowest  (~20 ms/step)

// Half-step sequence: 8 phases, smoothest motion for the 28BYJ-48.
// Each row = which coils (IN1..IN4) are energized.
const uint8_t PHASES[8][4] = {
  {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
  {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
};

int8_t direction = 1;      // +1 or −1
uint8_t phase = 0;
unsigned long lastStep = 0;

bool dirPressed() {
  static uint8_t stable = HIGH, last = HIGH;
  static unsigned long changed = 0;
  uint8_t raw = digitalRead(BTN_DIR);
  if (raw != last) { changed = millis(); last = raw; }
  if (millis() - changed > DEBOUNCE && raw != stable) {
    stable = raw;
    if (stable == LOW) return true;
  }
  return false;
}

void setup() {
  for (uint8_t c = 0; c < 4; c++) pinMode(COIL_PINS[c], OUTPUT);
  pinMode(BTN_DIR, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Stepper — pot = speed, button = reverse");
}

void loop() {
  if (dirPressed()) {
    direction = -direction;
    Serial.println(direction == 1 ? "→ forward" : "← reverse");
  }

  // pot → microsecond gap between steps (log-ish feel via map)
  int pot = analogRead(POT_PIN);
  unsigned long stepGap = map(pot, 0, 1023, STEP_MAX_US, STEP_MIN_US);

  unsigned long now = micros();
  if (now - lastStep < stepGap) return;      // not time yet — stays non-blocking
  lastStep = now;

  phase = (phase + direction + 8) % 8;       // +8 keeps % positive
  for (uint8_t c = 0; c < 4; c++)
    digitalWrite(COIL_PINS[c], PHASES[phase][c]);
}
