// 04 - Automatic Night Light
// 4-pin Light Sensor module (VCC, GND, AO, DO)
// LED turns ON when it is dark

const int AO_PIN  = A0;   // Analog output of the sensor
const int DO_PIN  = 2;    // Digital output of the sensor
const int LED_PIN = 9;    // LED

void setup() {
  pinMode(DO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  Serial.println("Automatic Night Light");
  Serial.println("4-pin light sensor (AO + DO)");
  Serial.println("----------------------------");
}

void loop() {
  int analogValue  = analogRead(AO_PIN);      // 0 (bright) ~ 1023 (dark)  - may be inverted on some modules
  int digitalValue = digitalRead(DO_PIN);     // HIGH or LOW

  Serial.print("AO: ");
  Serial.print(analogValue);
  Serial.print("   DO: ");
  Serial.println(digitalValue);

  // ----- Use Digital Output (recommended for beginners) -----
  // Most MS-CDS05 modules: DO = LOW when dark (after adjusting the potentiometer)
  // If your LED turns on when it is bright, change LOW to HIGH below.

  if (digitalValue == LOW) {
    digitalWrite(LED_PIN, HIGH);   // dark → LED ON
  } else {
    digitalWrite(LED_PIN, LOW);    // bright → LED OFF
  }

  delay(300);
}
