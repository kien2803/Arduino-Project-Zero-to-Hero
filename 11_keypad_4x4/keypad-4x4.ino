// 11 - Keypad 4x4
// Read pressed keys and print to Serial

#include <Keypad.h>   // Install "Keypad" library by Mark Stanley / Alexander Brevig

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};   // connect to row pins of keypad
byte colPins[COLS] = {5, 4, 3, 2};   // connect to column pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Serial.println("Keypad 4x4 Ready");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);
  }
}
