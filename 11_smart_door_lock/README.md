# 11 — Smart Door Lock (Flagship Project)

A complete smart door lock that feels like a real commercial product.

## What it does

- Shows “Scan card…” on the LCD.
- Authorized RFID card → green LED + short beep + “Access Granted” + servo unlocks for 3.5 seconds, then locks again.
- Unknown card → red LED + long beep + “Access Denied”.

This combines almost every skill you learned in the previous projects into one useful device.

## Components

| Item | Purpose |
|------|---------|
| Arduino Uno | Controller |
| RFID RC522 + cards | Identification |
| Micro Servo SG90 | Mechanical lock |
| LCD 1602 | User interface |
| Buzzer | Sound feedback |
| Red & Green LEDs | Visual feedback |
| 10 kΩ potentiometer | LCD contrast |
| Breadboard + wires | |

## Wiring Overview

**RFID RC522** (3.3 V only)
```
SDA	oD10  SCK	oD13  MOSI	oD11  MISO	oD12  RST	oD9  3.3V	o3.3V  GND	oGND
```

**Servo** → D6 (signal), 5V, GND  
**LCD** (4-bit) → RS=D12, E=D11, D4=D5, D5=D4, D6=D3, D7=D2  
**Buzzer** → D8  
**Green LED** → D7  
**Red LED** → A1

## Setup

1. First run Project 10 and copy your real card UID.
2. Paste it into the `authorizedUID` array.
3. Install library **MFRC522**.
4. Upload and test.

## Why this project matters

You just built the same core logic that appears in hotel locks, office access systems, and many smart home products — only simplified so you can understand every line of code.

## Possible next steps

- Add keypad as backup PIN entry.
- Store multiple cards in EEPROM.
- Add a master card that can enroll new users.
- Log access times via Serial or SD card.
