// 08 - Vibration Sensor SW-420
// Detect vibration / shock and light an LED + beep

int vibPin = 2;       // Digital output of SW-420
int ledPin = 13;
int buzzerPin = 8;

void setup() {
  pinMode(vibPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Vibration Sensor SW-420 Ready");
}

void loop() {
  int vibration = digitalRead(vibPin);

  if (vibration == HIGH) {          // Module usually HIGH when vibration detected
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000, 200);     // short beep
    Serial.println("Vibration detected!");
    delay(300);                     // simple debounce
  } else {
    digitalWrite(ledPin, LOW);
  }
}
