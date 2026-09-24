// 06 - LCD 1602 Display (parallel 4-bit mode)
// Simple Hello World + counter

#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int counter = 0;

void setup() {
  lcd.begin(16, 2);          // 16 columns, 2 rows
  lcd.print("Arduino Kit");
  lcd.setCursor(0, 1);
  lcd.print("LCD 1602 Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Counter:");
  lcd.setCursor(0, 1);
  lcd.print(counter);
  lcd.print("   ");          // clear leftover digits
  counter++;
  delay(1000);
}
