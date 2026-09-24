// 09 - Servo Barrier Gate
// Press a button to open the barrier, it closes automatically after a few seconds

#include <Servo.h>

Servo barrier;
const int servoPin  = 9;
const int buttonPin = 2;

void setup() {
  barrier.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  barrier.write(0);          // closed position
  Serial.begin(9600);
  Serial.println("Servo Barrier ready");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Opening barrier...");
    barrier.write(90);       // open
    delay(4000);             // stay open 4 seconds
    Serial.println("Closing barrier...");
    barrier.write(0);        // close
    delay(500);              // debounce
  }
}
