// 06 - Anti-Theft Vibration Alarm
// Beeps and lights an LED when vibration is detected

const int vibPin    = 2;
const int ledPin    = 13;
const int buzzerPin = 8;

void setup() {
  pinMode(vibPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Anti-Theft Alarm ready");
}

void loop() {
  if (digitalRead(vibPin) == HIGH) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1500, 300);   // short loud beep
    Serial.println("Vibration detected!");
    delay(400);                   // simple debounce
  } else {
    digitalWrite(ledPin, LOW);
  }
}
