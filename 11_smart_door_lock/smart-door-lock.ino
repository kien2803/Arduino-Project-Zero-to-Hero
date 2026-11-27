// 11 — Smart Door Lock (RFID + IR-remote PIN + LCD + Servo)
// Capstone: tap a registered card, then type a 4-digit PIN on the IR
// remote (the kit has no keypad — the remote's number keys do the job).
// LCD shows status, servo is the bolt, ring shows grant/deny.
//
// *** TEACHING DEMO, NOT A REAL LOCK ***
// UIDs are clonable, the PIN lives in firmware, and an SG90 is a demo
// bolt. This shows the SHAPE of a real system, not the security of one.

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

// ---- pins (note: LCD RS/E live on A2/A3 — NOT D11/D12, which are SPI) ----
const uint8_t RFID_SS = 10, RFID_RST = 9;      // SPI: 11,12,13
const uint8_t LCD_RS = A2, LCD_E = A3;         // freed from SPI pins!
const uint8_t LCD_D4 = 4, LCD_D5 = 5, LCD_D6 = 6, LCD_D7 = 7;
const uint8_t SERVO_PIN  = 8;
const uint8_t RING_PIN   = 2;
const uint8_t IR_PIN     = A1;
const uint8_t BUZZER     = A0;
const uint8_t NUM_LEDS   = 12;

const int8_t LOCKED_ANGLE = 0, OPEN_ANGLE = 90;
const unsigned long OPEN_MS    = 4000;   // door stays open this long
const unsigned long DENIED_MS  = 1500;
const unsigned long PIN_TIMEOUT = 10000; // give up typing after 10 s

// ---- edit these: paste your card UID + remote codes from Serial ----
const byte ALLOWED_UID[] = {0xDE, 0xAD, 0xBE, 0xEF};
const uint8_t PIN[4] = {1, 2, 3, 4};
// common 20-key NEC remote digit codes — verify on Serial, fix if wrong:
const uint8_t CMD_DIGIT[10] = {
  0x16, 0x0C, 0x18, 0x5E, 0x08, 0x1C, 0x5A, 0x42, 0x52, 0x4A  // 0..9
};
// -------------------------------------------------------------------

MFRC522 rfid(RFID_SS, RFID_RST);
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Adafruit_NeoPixel ring(NUM_LEDS, RING_PIN, NEO_GRB + NEO_KHZ800);
Servo bolt;

enum State { IDLE, ENTER_PIN, GRANTED, DENIED } state = IDLE;
unsigned long stateAt = 0;
uint8_t typed = 0, pinBuf[4];

void lcdStatus(const char *l1, const char *l2 = "") {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(l1);
  lcd.setCursor(0, 1); lcd.print(l2);
}

int8_t digitFromCmd(uint8_t cmd) {
  for (uint8_t d = 0; d < 10; d++) if (CMD_DIGIT[d] == cmd) return d;
  return -1;
}

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
  switch (s) {
    case IDLE:      lcdStatus("SMART DOOR LOCK", "Tap your card"); break;
    case ENTER_PIN: typed = 0; lcdStatus("Card OK — PIN:", ""); break;
    case GRANTED:
      bolt.write(OPEN_ANGLE);
      ring.fill(ring.Color(0, 180, 0)); ring.show();
      lcdStatus("ACCESS GRANTED", "Welcome!");
      tone(BUZZER, 1200, 120);
      Serial.println("GRANTED — door open");
      break;
    case DENIED:
      ring.fill(ring.Color(255, 0, 0)); ring.show();
      lcdStatus("ACCESS DENIED", "");
      tone(BUZZER, 300, 400);
      Serial.println("DENIED");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  lcd.begin(16, 2);
  bolt.attach(SERVO_PIN);
  bolt.write(LOCKED_ANGLE);
  ring.begin();
  pinMode(BUZZER, OUTPUT);
  setState(IDLE);
  Serial.print("RC522 firmware: 0x");
  Serial.println(rfid.PCD_ReadRegister(MFRC522::VersionReg), HEX);
}

void loop() {
  unsigned long now = millis();

  // ---- timed exits (non-blocking everywhere) ----
  if (state == GRANTED && now - stateAt >= OPEN_MS) {
    bolt.write(LOCKED_ANGLE);
    ring.clear(); ring.show();
    setState(IDLE);
    Serial.println("relocked");
  } else if (state == DENIED && now - stateAt >= DENIED_MS) {
    ring.clear(); ring.show();
    setState(IDLE);
  } else if (state == ENTER_PIN && now - stateAt >= PIN_TIMEOUT) {
    setState(DENIED);
    Serial.println("PIN timeout");
  }

  // ---- IR digit entry ----
  if (state == ENTER_PIN && IrReceiver.decode()) {
    auto &d = IrReceiver.decodedIRData;
    if (!(d.flags & IRDATA_FLAGS_IS_REPEAT)) {
      Serial.print("IR cmd=0x"); Serial.println(d.command, HEX);
      int8_t digit = digitFromCmd(d.command);
      if (digit >= 0) {
        pinBuf[typed++] = digit;
        lcd.setCursor(typed - 1, 1); lcd.print('*');
        tone(BUZZER, 800, 40);
        if (typed == 4) {
          bool ok = true;
          for (uint8_t i = 0; i < 4; i++) ok &= (pinBuf[i] == PIN[i]);
          setState(ok ? GRANTED : DENIED);
        }
      }
    }
    IrReceiver.resume();
  }

  // ---- card tap (only in IDLE) ----
  if (state == IDLE &&
      rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("UID: "); printUid(rfid.uid); Serial.println();
    setState(uidMatches(rfid.uid) ? ENTER_PIN : DENIED);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
