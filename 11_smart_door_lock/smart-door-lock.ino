// 11 - Smart Door Lock (Flagship)
// RFID + optional keypad feel + Servo + LCD + Buzzer + LEDs
// Authorized card opens the door for a few seconds

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorLock;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // RS, E, D4, D5, D6, D7

const int servoPin  = 6;
const int buzzerPin = 8;
const int greenLed  = 7;
const int redLed    = A1;

// Replace with your real card UID
byte authorizedUID[4] = {0xA1, 0xB2, 0xC3, 0xD4};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  doorLock.attach(servoPin);
  doorLock.write(0);               // locked

  lcd.begin(16, 2);
  lcd.print("Smart Door Lock");
  lcd.setCursor(0, 1);
  lcd.print("Scan card...");

  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  Serial.println("Smart Door Lock ready");
}

bool checkUID() {
  if (rfid.uid.size != 4) return false;
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) return false;
  }
  return true;
}

void accessGranted() {
  lcd.clear();
  lcd.print("Access Granted");
  lcd.setCursor(0, 1);
  lcd.print("Welcome!");
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  tone(buzzerPin, 1000, 180);

  doorLock.write(90);              // unlock
  delay(3500);
  doorLock.write(0);               // lock again

  digitalWrite(greenLed, LOW);
  lcd.clear();
  lcd.print("Door Locked");
  lcd.setCursor(0, 1);
  lcd.print("Scan card...");
}

void accessDenied() {
  lcd.clear();
  lcd.print("Access Denied");
  lcd.setCursor(0, 1);
  lcd.print("Unknown card");
  digitalWrite(redLed, HIGH);
  tone(buzzerPin, 280, 700);
  delay(1200);
  digitalWrite(redLed, LOW);
  lcd.clear();
  lcd.print("Smart Door Lock");
  lcd.setCursor(0, 1);
  lcd.print("Scan card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  Serial.print("Scanned UID:");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (checkUID()) accessGranted();
  else            accessDenied();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(400);
}
