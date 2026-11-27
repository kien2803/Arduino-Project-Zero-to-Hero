// 08 - Password Lock with Keypad
// Enter a 4-digit password. Correct = success beep + LED, wrong = error beep

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String password = "1234";   // change this
String input = "";

const int ledPin    = 13;
const int buzzerPin = 10;

const unsigned long GRANTED_MS = 1500;  // LED stays on this long after success
unsigned long grantedUntil = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.println("Password Lock ready");
  Serial.println("Enter 4-digit password, then #");
}

void loop() {
  // End of the "granted" window — non-blocking (was delay(1500)).
  if (grantedUntil && millis() >= grantedUntil) {
    digitalWrite(ledPin, LOW);
    grantedUntil = 0;
  }

  char key = keypad.getKey();
  if (!key) return;

  Serial.print(key);

  if (key == '#') {
    if (input == password) {
      Serial.println("  --> ACCESS GRANTED");
      digitalWrite(ledPin, HIGH);
      grantedUntil = millis() + GRANTED_MS;
      tone(buzzerPin, 1000, 200);
    } else {
      Serial.println("  --> WRONG PASSWORD");
      tone(buzzerPin, 300, 800);
    }
    input = "";
    Serial.println("Enter password again:");
  }
  else if (key == '*') {
    input = "";
    Serial.println("  (cleared)");
  }
  else if (input.length() < 4) {
    input += key;
  }
}
