// 10 — RFID Access Control (RC522 + NeoPixel feedback)
// Tap a registered card → green sweep on the ring + relay opens.
// Unknown card → red flash + deny. Teaches: SPI bus, UID matching,
// non-blocking timed grant, using the ring as a status display.
//
// *** TEACHING DEMO — not real security. MIFARE UIDs are readable
// and clonable; the whitelist is compiled into the firmware. ***

#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>

const uint8_t RFID_SS   = 10;
const uint8_t RFID_RST  = 9;
const uint8_t RELAY_PIN = 2;
const uint8_t RING_PIN  = 7;
const uint8_t NUM_LEDS  = 12;

const unsigned long GRANT_MS = 3000;   // how long access stays open
const unsigned long DENY_MS  = 1200;   // red-flash duration

// ---- paste your card's UID here (printed on Serial on first tap) ----
const byte ALLOWED_UID[] = {0xDE, 0xAD, 0xBE, 0xEF};
// --------------------------------------------------------------------

MFRC522 rfid(RFID_SS, RFID_RST);
Adafruit_NeoPixel ring(NUM_LEDS, RING_PIN, NEO_GRB + NEO_KHZ800);

enum State { IDLE, GRANTED, DENIED } state = IDLE;
unsigned long stateAt = 0;

bool uidMatches(const MFRC522::Uid &u) {
  if (u.size != sizeof(ALLOWED_UID)) return false;
  for (uint8_t i = 0; i < u.size; i++)
    if (u.uidByte[i] != ALLOWED_UID[i]) return false;
  return true;
}

void printUid(const MFRC522::Uid &u) {
  for (uint8_t i = 0; i < u.size; i++) {
    if (u.uidByte[i] < 0x10) Serial.print('0');
    Serial.print(u.uidByte[i], HEX); Serial.print(' ');
  }
}

void setState(State s) {
  state = s; stateAt = millis();
  if (s == GRANTED) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("ACCESS GRANTED");
  } else if (s == DENIED) {
    Serial.println("ACCESS DENIED");
  }
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(RELAY_PIN, OUTPUT);
  ring.begin();
  Serial.print("RC522 firmware: 0x"); Serial.println(rfid.PCD_ReadRegister(MFRC522::VersionReg), HEX);
  Serial.println("RFID access — tap a card");
}

void loop() {
  // --- timed return to IDLE (non-blocking — this replaced delay()) ---
  if (state == GRANTED && millis() - stateAt >= GRANT_MS) {
    digitalWrite(RELAY_PIN, LOW);
    ring.clear(); ring.show();
    state = IDLE;
    Serial.println("relocked");
  } else if (state == DENIED && millis() - stateAt >= DENY_MS) {
    ring.clear(); ring.show();
    state = IDLE;
  }

  // --- feedback animation while in a state ---
  if (state == GRANTED) {                      // green sweep
    uint8_t head = (millis() / 60) % NUM_LEDS;
    ring.clear();
    ring.setPixelColor(head, ring.Color(0, 255, 0));
    ring.setPixelColor((head + 1) % NUM_LEDS, ring.Color(0, 120, 0));
    ring.show();
  } else if (state == DENIED && (millis() / 200) % 2) {  // red blink
    ring.fill(ring.Color(255, 0, 0)); ring.show();
  } else if (state == DENIED) {
    ring.clear(); ring.show();
  }

  // --- new card? ---
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  Serial.print("UID: "); printUid(rfid.uid); Serial.println();
  setState(uidMatches(rfid.uid) ? GRANTED : DENIED);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
