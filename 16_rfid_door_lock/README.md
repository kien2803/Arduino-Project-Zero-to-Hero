# 16 — RFID Door Lock (Flagship Project)

Complete access-control system using almost every major module in the BanLinhKien Arduino Uno R3 RFID kit.

**Features**
- Scan RFID card / keyfob
- Authorized card → Servo opens (door unlock) + Green LED + Welcome on LCD + short beep
- Unauthorized card → Red LED + Access Denied on LCD + long beep
- Automatically locks again after 3 seconds

## Components used (from your kit)

| Component | Purpose |
|-----------|---------|
| Arduino UNO R3 | Brain |
| RFID RC522 + Card/Tag | Identification |
| Servo SG90 | Door lock actuator |
| LCD1602 | User feedback |
| Còi Chip 5V | Audio feedback |
| LED đỏ + xanh | Visual feedback |
| Potentiometer B10K | LCD contrast |
| Breadboard + wires | Connections |

## Wiring Summary

**RFID RC522** (3.3 V only!)
```
SDA	oD10 | SCK	oD13 | MOSI	oD11 | MISO	oD12 | RST	oD9 | 3.3V	o3.3V | GND	oGND
```

**Servo SG90**
```
Signal	oD6 | VCC	o5V | GND	oGND
```

**LCD1602 (4-bit)**
```
RS	oD12 | E	oD11 | D4	oD5 | D5	oD4 | D6	oD3 | D7	oD2
VSS	oGND | VDD	o5V | V0	oPot wiper | A	o5V | K	oGND | RW	oGND
```

**Buzzer** 	o D8 (+) / GND  
**Green LED** 	o D7 (+ resistor)  
**Red LED** 	o A1 (+ resistor)

## Important Setup Steps

1. First run **Project 13** to read the real UID of your card.
2. Copy the 4-byte UID into the array `authorizedUID` in this sketch.
3. Install libraries: **MFRC522**, **Servo** (built-in), **LiquidCrystal** (built-in).
4. Upload and test.

## How to add more cards

You can expand `checkUID()` to compare against multiple stored UIDs (array of arrays) or even store them in EEPROM.

## Possible Upgrades

- Add Keypad for PIN backup.
- Use Relay instead of (or together with) Servo for electric lock.
- Add master card to enroll new cards.
- Send log via Serial or ESP32 later.

This project is the perfect finale of the kit and a strong portfolio piece!
