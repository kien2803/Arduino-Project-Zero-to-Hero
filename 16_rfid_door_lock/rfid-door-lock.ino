// 16 - RFID Door Lock (Flagship Project)
// RFID + Servo + LCD + Buzzer + LED
// Authorized card -> open door (servo) + welcome message
// Unauthorized -> access denied + beep

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // RS, E, D4, D5, D6, D7

const int servoPin = 6;
const int buzzerPin = 8;
const int greenLed = 7;
const int redLed = A1;   // using analog pin as digital

// REPLACE THESE WITH YOUR REAL CARD UIDs (from project 13)
byte authorizedUID[4] = {0x12, 0x34, 0x56, 0x78};  // example - change me!

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  doorServo.attach(servoPin);
  doorServo.write(0);  // locked position

  lcd.begin(16, 2);
  lcd.print("RFID Door Lock");
  lcd.setCursor(0, 1);
  lcd.print("Scan your card");

  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  Serial.println("RFID Door Lock Ready");
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
  tone(buzzerPin, 1000, 200);

  doorServo.write(90);   // open
  delay(3000);           // keep open 3 seconds
  doorServo.write(0);    // lock again

  digitalWrite(greenLed, LOW);
  lcd.clear();
  lcd.print("Door Locked");
  lcd.setCursor(0, 1);
  lcd.print("Scan your card");
}

void accessDenied() {
  lcd.clear();
  lcd.print("Access Denied");
  lcd.setCursor(0, 1);
  lcd.print("Unknown card");
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  tone(buzzerPin, 300, 800);  // long low beep
  delay(1500);
  digitalWrite(redLed, LOW);
  lcd.clear();
  lcd.print("RFID Door Lock");
  lcd.setCursor(0, 1);
  lcd.print("Scan your card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("Scanned UID:");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (checkUID()) {
    accessGranted();
  } else {
    accessDenied();
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(500);
}
