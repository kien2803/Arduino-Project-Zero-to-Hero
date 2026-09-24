// 10 - IR Remote + Receiver 1838T
// Decode remote buttons and print to Serial + control LED

#include <IRremote.hpp>   // Install "IRremote" library by shirriff / ArminJo

const int RECV_PIN = 11;
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Remote Ready - Press any button");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Code: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    // Example: toggle LED on any button (you can map specific codes later)
    digitalWrite(ledPin, !digitalRead(ledPin));

    IrReceiver.resume();
  }
}
