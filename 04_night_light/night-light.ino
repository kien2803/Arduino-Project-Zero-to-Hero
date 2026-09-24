// 04 - Automatic Night Light
// Turns an LED on when the environment becomes dark

const int lightPin = A0;   // Light sensor (analog)
const int ledPin   = 9;    // LED (PWM capable)
const int threshold = 400; // Adjust this value to your room

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Automatic Night Light ready");
}

void loop() {
  int lightLevel = analogRead(lightPin);
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  if (lightLevel < threshold) {
    // Dark → turn LED on (you can also use analogWrite for soft brightness)
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(200);
}
