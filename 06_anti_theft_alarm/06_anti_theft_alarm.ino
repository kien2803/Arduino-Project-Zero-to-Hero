// 06 - Anti-Theft Vibration Alarm
// Beeps and lights the LED when vibration is detected.
// LED stays on for ALARM_MS after the last shock (non-blocking).

const int vibPin    = 2;   // sensor module DO (active HIGH on shock)
const int ledPin    = 13;
const int buzzerPin = 8;

const unsigned long ALARM_MS = 1500;  // LED/alarm hold time after a shock

unsigned long alarmUntil = 0;
int lastVib = LOW;

void setup() {
  pinMode(vibPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Anti-Theft Alarm ready");
}

void loop() {
  int vib = digitalRead(vibPin);

  if (vib == HIGH && lastVib == LOW) {   // rising edge = new shock
    alarmUntil = millis() + ALARM_MS;
    tone(buzzerPin, 1500, 300);          // short loud beep (non-blocking)
    Serial.println("Vibration detected!");
  }
  lastVib = vib;

  digitalWrite(ledPin, millis() < alarmUntil ? HIGH : LOW);
}
