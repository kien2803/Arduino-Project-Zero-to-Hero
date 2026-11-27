int ledPin = 9;
int potPin = A0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);

  int brightness = map(potValue, 0, 1023, 0, 255);

  analogWrite(ledPin, brightness);
}