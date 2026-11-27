// 01 - Traffic Light
// Cycles a red / green / yellow LED sequence like a real intersection light.

const int ledRed    = 13;
const int ledYellow = 12;
const int ledGreen  = 11;

// Phase durations in milliseconds — retune the whole cycle in one place.
const unsigned long RED_MS    = 5000;
const unsigned long GREEN_MS  = 4000;
const unsigned long YELLOW_MS = 2000;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
}

void setLights(bool red, bool yellow, bool green) {
  digitalWrite(ledRed, red ? HIGH : LOW);
  digitalWrite(ledYellow, yellow ? HIGH : LOW);
  digitalWrite(ledGreen, green ? HIGH : LOW);
}

void loop() {
  setLights(true, false, false);   // RED: vehicles must stop
  delay(RED_MS);

  setLights(false, false, true);   // GREEN: vehicles may go
  delay(GREEN_MS);

  setLights(false, true, false);   // YELLOW: caution / transition
  delay(YELLOW_MS);
}
