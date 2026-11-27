// 11 - Smart Door Lock (Flagship)
// RFID card + Servo lock + LCD + buzzer + status LEDs.
//
// NOTE ON PINS: the RC522 needs SPI (D11 MOSI, D12 MISO, D13 SCK, D10 SS).
// The LCD is a *parallel* display, so its RS/E lines were moved to A2/A3 —
// do NOT wire the LCD to D11/D12, they belong to SPI.
//
// SECURITY NOTE: UID matching is an educational demonstration. Card UIDs
// are not secret — they can be read and cloned. A production lock needs
// real authentication (e.g. MIFARE sector auth) plus a secure backend.

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define SS_PIN  10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorLock;
LiquidCrystal lcd(A2, A3, 5, 4, 3, 2);  // RS, E, D4, D5, D6, D7 (off SPI pins!)

const int servoPin  = 6;
const int buzzerPin = 8;
const int greenLed  = 7;
const int redLed    = A1;

const int LOCKED_ANGLE   = 0;
const int UNLOCKED_ANGLE = 90;

const unsigned long OPEN_MS   = 3500;  // door stays unlocked this long
const unsigned long DENIED_MS = 1200;  // "access denied" feedback length

// Replace with your real card UID (scan it with project 10 first).
byte authorizedUID[4] = {0xA1, 0xB2, 0xC3, 0xD4};

// State machine: loop() never blocks, so the LCD/LEDs/timers stay live.
enum State { IDLE, GRANTED, DENIED };
State state = IDLE;
unsigned long stateEnteredAt = 0;

void showIdleScreen() {
  lcd.clear();
  lcd.print("Smart Door Lock");
  lcd.setCursor(0, 1);
  lcd.print("Scan card...");
}

void enterIdle() {
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
  doorLock.write(LOCKED_ANGLE);
  showIdleScreen();
  state = IDLE;
}

void enterGranted() {
  lcd.clear();
  lcd.print("Access Granted");
  lcd.setCursor(0, 1);
  lcd.print("Welcome!");
  digitalWrite(greenLed, HIGH);
  tone(buzzerPin, 1000, 180);
  doorLock.write(UNLOCKED_ANGLE);
  stateEnteredAt = millis();
  state = GRANTED;
}

void enterDenied() {
  lcd.clear();
  lcd.print("Access Denied");
  lcd.setCursor(0, 1);
  lcd.print("Unknown card");
  digitalWrite(redLed, HIGH);
  tone(buzzerPin, 280, 700);
  doorLock.write(LOCKED_ANGLE);   // stays locked
  stateEnteredAt = millis();
  state = DENIED;
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  doorLock.attach(servoPin);
  lcd.begin(16, 2);

  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  enterIdle();
  Serial.println("Smart Door Lock ready");
}

bool checkUID() {
  if (rfid.uid.size != 4) return false;
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) return false;
  }
  return true;
}

void pollCard() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  Serial.print("Scanned UID:");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  if (rfid.uid.size != 4) Serial.print("  (non-4-byte UID)");
  Serial.println();

  if (checkUID()) enterGranted();
  else            enterDenied();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void loop() {
  unsigned long now = millis();
  switch (state) {
    case IDLE:
      pollCard();
      break;

    case GRANTED:
      if (now - stateEnteredAt >= OPEN_MS) {
        Serial.println("Locking");
        enterIdle();
      }
      break;

    case DENIED:
      if (now - stateEnteredAt >= DENIED_MS) {
        enterIdle();
      }
      break;
  }
}
