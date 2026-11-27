// 09 - Servo Barrier Gate
// Press the button: the barrier opens for OPEN_MS then closes by itself.
//
// Non-blocking design: a 2-state machine driven by millis(), so loop()
// keeps running and the board stays responsive (e.g. an emergency-close
// button could be added later without rewriting the timing).

#include <Servo.h>

Servo barrier;

const int servoPin  = 9;
const int buttonPin = 2;            // button between D2 and GND (INPUT_PULLUP)

const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE   = 90;

const unsigned long OPEN_MS     = 4000;  // how long the barrier stays up
const unsigned long DEBOUNCE_MS = 30;    // button debounce

enum State { CLOSED, OPEN };
State state = CLOSED;

unsigned long openedAt  = 0;
int lastRawButton       = HIGH;
int stableButton        = HIGH;
unsigned long lastEdge  = 0;

void setup() {
  barrier.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  barrier.write(CLOSED_ANGLE);
  Serial.begin(9600);
  Serial.println("Servo Barrier ready — CLOSED");
}

// Debounced falling-edge detection: true ONCE per real press.
bool buttonPressed() {
  int raw = digitalRead(buttonPin);
  if (raw != lastRawButton) {
    lastEdge = millis();          // input changed — restart debounce timer
    lastRawButton = raw;
  }
  if (millis() - lastEdge > DEBOUNCE_MS && raw != stableButton) {
    stableButton = raw;           // input stable → accept the new state
    if (stableButton == LOW) return true;   // falling edge = press
  }
  return false;
}

void loop() {
  switch (state) {
    case CLOSED:
      if (buttonPressed()) {
        Serial.println("OPEN");
        barrier.write(OPEN_ANGLE);
        openedAt = millis();
        state = OPEN;
      }
      break;

    case OPEN:
      if (millis() - openedAt >= OPEN_MS) {
        Serial.println("CLOSED");
        barrier.write(CLOSED_ANGLE);
        state = CLOSED;
      }
      break;
  }
}
