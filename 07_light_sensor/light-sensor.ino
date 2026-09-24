// 07 - Light Sensor MS-CDS05
// Read ambient light and control LED brightness or threshold

int sensorPin = A0;   // Analog output of light sensor module
int ledPin = 9;       // PWM LED
int threshold = 500;  // Adjust according to your environment

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Light Sensor Ready");
}

void loop() {
  int lightValue = analogRead(sensorPin);  // 0 (dark) ~ 1023 (bright) - check module polarity
  Serial.print("Light: ");
  Serial.println(lightValue);

  // Example 1: LED brightness inverse to light (night light)
  int brightness = map(lightValue, 0, 1023, 255, 0);
  analogWrite(ledPin, brightness);

  // Example 2: Digital threshold (uncomment if preferred)
  // if (lightValue < threshold) {
  //   digitalWrite(ledPin, HIGH);  // Turn on when dark
  // } else {
  //   digitalWrite(ledPin, LOW);
  // }

  delay(200);
}
