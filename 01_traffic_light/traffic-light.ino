// --- PIN DECLARATION ---
int ledRed = 13;
int ledYellow = 12;
int ledGreen = 11;

void setup() {
  // Configure pins 13, 12, 11 as OUTPUT signals
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  // --- PHASE 1: RED LIGHT ON FOR 5 SECONDS ---
  digitalWrite(ledRed, HIGH);    // Turn on Red (HIGH = 5V)
  digitalWrite(ledYellow, LOW);  // Turn off Yellow (LOW = 0V)
  digitalWrite(ledGreen, LOW);   // Turn off Green
  delay(5000);                   // Wait 5000 ms (5 seconds)

  // --- PHASE 2: GREEN LIGHT ON FOR 4 SECONDS ---
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, HIGH);  // Turn on Green
  delay(4000);                   // Wait 4 seconds

  // --- PHASE 3: YELLOW LIGHT ON FOR 2 SECONDS ---
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, HIGH); // Turn on Yellow
  digitalWrite(ledGreen, LOW);
  delay(2000);                   // Wait 2 seconds
}