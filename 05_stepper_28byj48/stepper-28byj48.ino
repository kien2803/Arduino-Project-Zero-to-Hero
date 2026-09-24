// 05 - Stepper Motor 28BYJ-48 + ULN2003
// Rotate clockwise then counter-clockwise

#include <Stepper.h>

const int stepsPerRevolution = 2048;  // 28BYJ-48 with ULN2003 (full step)

// ULN2003 pins connected to Arduino
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(10);  // RPM
  Serial.begin(9600);
  Serial.println("Stepper 28BYJ-48 Ready");
}

void loop() {
  Serial.println("Clockwise");
  myStepper.step(stepsPerRevolution);   // 1 full revolution CW
  delay(1000);

  Serial.println("Counter-clockwise");
  myStepper.step(-stepsPerRevolution);  // 1 full revolution CCW
  delay(1000);
}
