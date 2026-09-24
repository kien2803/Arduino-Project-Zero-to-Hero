// 12 - 7-Segment 1 Digit (Common Anode)
// Count 0-9 on the single digit display

// Pin mapping for segments a b c d e f g (common anode)
// Adjust if your wiring is different
const int segPins[] = {2, 3, 4, 5, 6, 7, 8}; // a,b,c,d,e,f,g

// Common Anode patterns (0 = ON, 1 = OFF because anode is common +)
const byte digits[10] = {
  B0000001, // 0  (g off)
  B1001111, // 1
  B0010010, // 2
  B0000110, // 3
  B1001100, // 4
  B0100100, // 5
  B0100000, // 6
  B0001111, // 7
  B0000000, // 8
  B0000100  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
}

void displayDigit(int num) {
  byte pattern = digits[num];
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], bitRead(pattern, 6 - i)); // MSB first
  }
}

void loop() {
  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    delay(800);
  }
}
