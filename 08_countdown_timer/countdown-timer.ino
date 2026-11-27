// 08 — Countdown Timer (4-digit 7-segment)
// The hard concept: multiplexing — 12 pins drive 32 segments by
// lighting one digit at a time, faster than the eye can see.
// Buttons set/start the timer, buzzer rings at 00:00.

// Segment pins a,b,c,d,e,f,g,dp → D2..D9
const uint8_t SEG_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
// Digit cathodes (common-cathode display): digit ON = pin LOW
const uint8_t DIG_PINS[4] = {10, 11, 12, 13};

const uint8_t BTN_SET   = A0;   // +1 minute while stopped (to GND)
const uint8_t BTN_START = A1;   // start/pause (to GND)
const uint8_t BUZZER    = A2;   // active buzzer

const unsigned long DIGIT_MS   = 2;      // per-digit display time (~125 Hz full frame)
const unsigned long DEBOUNCE   = 40;

// bit0=a … bit6=g, bit7=dp. 1 = ON.
const uint8_t DIGITS[10] = {
  0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
  0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111
};

uint8_t frame[4];              // what each digit shows (raw patterns)
enum State { SET, RUNNING, RINGING } state = SET;
unsigned long remainMs = 0, lastTick = 0;

void showDigit(uint8_t pos, uint8_t pattern, bool dp = false) {
  for (uint8_t s = 0; s < 8; s++)
    digitalWrite(SEG_PINS[s], ((pattern >> s) & 1) ? HIGH : LOW);
  if (dp) digitalWrite(SEG_PINS[7], HIGH);
  digitalWrite(DIG_PINS[pos], LOW);         // enable this digit
}

void render(uint16_t seconds, bool colonOn) {
  uint8_t mm = seconds / 60, ss = seconds % 60;
  frame[0] = DIGITS[mm / 10]; frame[1] = DIGITS[mm % 10];
  frame[2] = DIGITS[ss / 10]; frame[3] = DIGITS[ss % 10];
  // blink the colon: use dp of digit1 as the separator dot
  if (colonOn) frame[1] |= 0b10000000;
}

bool pressed(uint8_t pin) {
  static uint8_t stable[20], last[20];
  static unsigned long changed[20];
  static bool first = true;
  if (first) {                       // one-time init: all pins "released"
    first = false;
    for (uint8_t i = 0; i < 20; i++) stable[i] = last[i] = HIGH;
  }
  uint8_t raw = digitalRead(pin);
  if (raw != last[pin]) { changed[pin] = millis(); last[pin] = raw; }
  if (millis() - changed[pin] > DEBOUNCE && raw != stable[pin]) {
    stable[pin] = raw;
    if (stable[pin] == LOW) return true;
  }
  return false;
}

void setup() {
  for (uint8_t s = 0; s < 8; s++) pinMode(SEG_PINS[s], OUTPUT);
  for (uint8_t d = 0; d < 4; d++) { pinMode(DIG_PINS[d], OUTPUT); digitalWrite(DIG_PINS[d], HIGH); }
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  Serial.println("Countdown — SET adds a minute, START runs it");
  render(60, false);
}

void loop() {
  // ---- display multiplexing: one digit lit per pass, every DIGIT_MS ----
  static uint8_t pos = 0;
  static unsigned long lastDigit = 0;
  if (millis() - lastDigit >= DIGIT_MS) {
    lastDigit = millis();
    digitalWrite(DIG_PINS[pos], HIGH);            // blank current
    pos = (pos + 1) % 4;
    showDigit(pos, frame[pos]);
  }

  // ---- timer engine ----
  if (state == RUNNING && millis() - lastTick >= 100) {
    lastTick += 100;
    if (remainMs > 100) remainMs -= 100; else remainMs = 0;
    render(remainMs / 1000, (millis() / 500) % 2);
    if (remainMs == 0) { state = RINGING; lastTick = millis(); }
  }
  if (state == RINGING) {
    digitalWrite(BUZZER, (millis() / 200) % 2);   // beep-beep-beep
    render(0, (millis() / 200) % 2);
    if (millis() - lastTick > 5000) { digitalWrite(BUZZER, LOW); state = SET; }
  }

  // ---- input ----
  if (state == SET && pressed(BTN_SET)) {
    remainMs = (remainMs + 60000UL) % (60000UL * 100);   // +1 min, cap 99:59
    render(remainMs / 1000, false);
  }
  if (pressed(BTN_START)) {
    if (state == SET && remainMs > 0) { state = RUNNING; lastTick = millis(); }
    else if (state == RUNNING)        { state = SET; }
    else if (state == RINGING)        { digitalWrite(BUZZER, LOW); state = SET; }
  }
}
