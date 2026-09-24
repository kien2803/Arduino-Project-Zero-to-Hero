// 04 - Servo SG90 Control
// Sweep servo from 0 to 180 degrees and back

#include <Servo.h>

Servo myServo;
int servoPin = 9;   // Signal pin of SG90

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("Servo SG90 Ready");
}

void loop() {
  // Sweep from 0 to 180
  for (int pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);
    delay(15);
  }
  delay(500);

  // Sweep from 180 to 0
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(15);
  }
  delay(500);
}
