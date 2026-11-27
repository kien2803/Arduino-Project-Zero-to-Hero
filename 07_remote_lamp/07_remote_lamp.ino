// 07 - Remote Controlled Lamp
// Toggle a relay (lamp) with any button on the IR remote

#include <IRremote.hpp>

const int RECV_PIN = 11;
const int relayPin = 7;

bool lampState = false;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Remote Controlled Lamp ready");
  Serial.println("Press any button on the remote to toggle");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Received: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    lampState = !lampState;
    digitalWrite(relayPin, lampState ? HIGH : LOW);
    Serial.println(lampState ? "Lamp ON" : "Lamp OFF");

    IrReceiver.resume();
    delay(300);   // avoid multiple triggers from one press
  }
}
