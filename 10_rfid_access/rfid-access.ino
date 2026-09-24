// 10 - RFID Access Control (basic)
// Only an authorized card turns the LED on and gives a success beep

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

// Replace with the UID you get from scanning your own card
byte authorizedUID[4] = {0xA1, 0xB2, 0xC3, 0xD4};

const int ledPin    = 7;
const int buzzerPin = 8;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.println("RFID Access Control ready");
  Serial.println("Scan a card...");
}

bool isAuthorized() {
  if (rfid.uid.size != 4) return false;
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) return false;
  }
  return true;
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID:");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (isAuthorized()) {
    Serial.println("Access granted");
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000, 200);
    delay(2000);
    digitalWrite(ledPin, LOW);
  } else {
    Serial.println("Access denied");
    tone(buzzerPin, 300, 700);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(500);
}
