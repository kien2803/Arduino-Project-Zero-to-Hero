// 07 - Remote Controlled Lamp
// Toggle a relay (lamp) with ONE specific button on the IR remote.
//
// Setup step for YOUR remote: upload once, press buttons, read each
// "command=0x.." line on Serial, then paste the command of the button
// you want into CMD_POWER below and upload again.

#include <IRremote.hpp>

const int RECV_PIN = 11;
const int relayPin = 7;

const uint8_t CMD_POWER = 0x45;   // example: POWER on many NEC remotes

bool lampState = false;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Remote Controlled Lamp ready");
  Serial.println("Press remote buttons to see their command codes.");
}

void loop() {
  if (!IrReceiver.decode()) return;

  IRData &data = IrReceiver.decodedIRData;

  // NEC-style protocols re-send a "repeat" frame while the button is held.
  // Ignoring them is what stops the relay from toggling many times per press.
  if (data.flags & IRDATA_FLAGS_IS_REPEAT) {
    IrReceiver.resume();
    return;
  }

  Serial.print("protocol=");
  Serial.print(IrReceiver.getProtocolString());
  Serial.print(" command=0x");
  Serial.println(data.command, HEX);
  IrReceiver.resume();               // ready for the next frame

  if (data.command == CMD_POWER) {
    lampState = !lampState;
    digitalWrite(relayPin, lampState ? HIGH : LOW);
    Serial.println(lampState ? "Lamp ON" : "Lamp OFF");
  }
}
