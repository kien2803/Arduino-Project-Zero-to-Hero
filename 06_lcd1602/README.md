# 06 — LCD 1602 (Green)

Display text and a live counter on the 16×2 character LCD included in the kit.

## Description

The LCD1602 is a classic parallel character display. This project uses 4-bit mode (saves Arduino pins) to show a welcome message and an incrementing counter.

## Components (from kit)

| # | Component | Qty | Notes |
|---|-----------|-----|-------|
| 1 | Arduino UNO R3 | 1 | |
| 1 | LCD1602 Xanh Lá 5V | 1 | 16 characters × 2 lines |
| 1 | Potentiometer B10K | 1 | Contrast adjustment |
| — | Jumper wires | ~10 | |
| — | Breadboard | 1 | Recommended |

## Wiring (4-bit mode)

```
LCD1602 pin     Arduino / Pot
-----------     -------------
VSS (1)     --> GND
VDD (2)     --> 5V
V0  (3)     --> Middle pin of B10K (contrast)
RS  (4)     --> D12
RW  (5)     --> GND  (write only)
E   (6)     --> D11
D4  (11)    --> D5
D5  (12)    --> D4
D6  (13)    --> D3
D7  (14)    --> D2
A   (15)    --> 5V   (backlight +)
K   (16)    --> GND  (backlight -)

Potentiometer B10K:
  One outer pin --> 5V
  Other outer  --> GND
  Wiper        --> LCD V0
```

## Code Highlights

- `#include <LiquidCrystal.h>`
- `LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);`
- `lcd.begin(16, 2);`
- `lcd.setCursor(col, row);` + `lcd.print();`

## Upload & Run

After uploading you should see “Arduino Kit” then a counting number. Adjust the potentiometer until the text is clear (not too dark or washed out).

## Extensions

- Display temperature from NTC module.
- Show RFID card UID.
- Create a simple menu with Keypad.
