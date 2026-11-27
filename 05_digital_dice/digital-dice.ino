// 05 — Digital Dice
// One-digit 7-segment display + pushbutton = electronic die.
// Teaches: segment pattern arrays, random(), debounced button input.

// Segment pins: a..g on D2..D8 (common-anode display → LOW lights a segment)
const uint8_t SEG_PINS[7] = {2, 3, 4, 5, 6, 7, 8};
const uint8_t BUTTON_PIN = 9;          // button → GND, uses INPUT_PULLUP
const unsigned long DEBOUNCE_MS = 40;
const unsigned long SHUFFLE_MS = 600;  // rolling animation length

// Bit patterns: bit0=a ... bit6=g. 1 = segment ON.
const uint8_t DIGITS[7] = {
  0b0000000,                    // (unused index 0)
  0b0000110,                    // 1: b,c
  0b1011011,                    // 2: a,b,g,e,d
  0b1001111,                    // 3: a,b,c,d,g
  0b1100110,                    // 4: f,g,b,c
  0b1101101,                    // 5: a,f,g,c,d
  0b1111101                     // 6: a,f,g,e,c,d
};

void showDigit(uint8_t n) {
  for (uint8_t s = 0; s < 7; s++)
    digitalWrite(SEG_PINS[s], (DIGITS[n] >> s) & 1 ? LOW : HIGH);
}

bool pressed() {               // true once per debounced press
  static uint8_t stable = HIGH, last = HIGH;
  static unsigned long changed = 0;
  uint8_t raw = digitalRead(BUTTON_PIN);
  if (raw != last) { changed = millis(); last = raw; }
  if (millis() - changed > DEBOUNCE_MS && raw != stable) {
    stable = raw;
    if (stable == LOW) return true;
  }
  return false;
}

void setup() {
  for (uint8_t s = 0; s < 7; s++) pinMode(SEG_PINS[s], OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  randomSeed(analogRead(A0));          // noise on a floating pin seeds random
  Serial.begin(9600);
  Serial.println("Digital dice — press the button to roll");
  showDigit(random(1, 7));
}

void loop() {
  static bool rolling = false;
  static unsigned long rollStart = 0, lastFlicker = 0;

  if (pressed() && !rolling) {         // start a roll
    rolling = true;
    rollStart = millis();
  }

  if (rolling) {
    if (millis() - lastFlicker > 60) { // flicker through faces
      lastFlicker = millis();
      showDigit(random(1, 7));
    }
    if (millis() - rollStart > SHUFFLE_MS) {
      rolling = false;
      uint8_t result = random(1, 7);
      showDigit(result);
      Serial.print("rolled: "); Serial.println(result);
    }
  }
}
