# 06 — LCD 1602

Display text and a live counter on a classic 16×2 character LCD.

## Description

The LCD1602 is a widely used parallel character display. This project uses 4-bit mode (saves Arduino pins) to show a welcome message followed by an incrementing counter.

## Components

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno | 1 | |
| LCD 1602 | 1 | 16 characters × 2 lines |
| Potentiometer 10 kΩ | 1 | Contrast adjustment |
| Jumper wires | ~10 | |
| Breadboard | 1 | Recommended |

## Wiring (4-bit mode)

```
LCD pin     Connection
-------     ----------
VSS (1) --> GND
VDD (2) --> 5V
V0  (3) --> Wiper of 10 kΩ potentiometer
RS  (4) --> D12
RW  (5) --> GND (write only)
E   (6) --> D11
D4 (11) --> D5
D5 (12) --> D4
D6 (13) --> D3
D7 (14) --> D2
A  (15) --> 5V (backlight +)
K  (16) --> GND (backlight -)

Potentiometer:
  One outer pin --> 5V
  Other outer  --> GND
  Wiper        --> LCD V0
```

## How It Works

- `#include <LiquidCrystal.h>`
- `LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);`
- `lcd.begin(16, 2);` initializes the display.
- `lcd.setCursor(col, row);` + `lcd.print();` write text.

## Upload & Run

After uploading you should see “Arduino Kit” then a counting number. Adjust the potentiometer until the characters are sharp and clear.

## Extensions

- Show temperature from the NTC sensor.
- Display RFID card UID.
- Build a simple menu controlled by the keypad.
