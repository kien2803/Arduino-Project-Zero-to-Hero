// 04 - Automatic Night Light
// Uses a 4-pin light sensor module (VCC, GND, AO, DO)
// Turns on an LED when it gets dark

// Light sensor pins
const int AO_PIN = A0;   // Analog output
const int DO_PIN = 2;    // Digital output (threshold set by potentiometer on module)

// LED pin (you can use a normal LED or one channel of RGB LED)
const int ledPin = 9;

void setup() {
  pinMode(DO_PIN, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Automatic Night Light ready");
  Serial.println("Using 4-pin light sensor (AO + DO)");
}

void loop() {
  int analogValue = analogRead(AO_PIN);     // 0 ~ 1023
  int digitalValue = digitalRead(DO_PIN);   // HIGH or LOW

  Serial.print("AO: ");
  Serial.print(analogValue);
  Serial.print("  |  DO: ");
  Serial.println(digitalValue == HIGH ? "HIGH (bright)" : "LOW (dark)");

  // Method 1: Use Digital Output (easiest)
  // Many modules: DO = LOW when dark (depends on the potentiometer)
  if (digitalValue == LOW) {
    digitalWrite(ledPin, HIGH);   // turn LED on when dark
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Method 2: Use Analog Output (more flexible)
  // Uncomment the block below if you prefer analog control
  /*
  const int threshold = 400;      // adjust to your room
  if (analogValue < threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  */

  delay(200);
}
