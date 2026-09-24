# 16 — RFID Door Lock (Flagship Project)

A complete access-control system that combines multiple modules into one practical application.

**Features**
- Scan an RFID card or key fob
- Authorized card → servo opens (unlock) + green LED + welcome message on LCD + short beep
- Unauthorized card → red LED + “Access Denied” on LCD + long beep
- Door automatically locks again after a few seconds

## Components

| Item | Purpose |
|------|---------|
| Arduino Uno | Main controller |
| RFID RC522 + cards/tags | Identification |
| Micro Servo SG90 | Lock actuator |
| LCD 1602 | User feedback |
| Buzzer | Audio feedback |
| Red & Green LEDs | Visual feedback |
| Potentiometer 10 kΩ | LCD contrast |
| Breadboard + jumper wires | Connections |

## Wiring Summary

**RFID RC522** (use 3.3 V only!)
```
SDA → D10 | SCK → D13 | MOSI → D11 | MISO → D12 | RST → D9 | 3.3V → 3.3V | GND → GND
```

**Servo SG90**
```
Signal → D6 | VCC → 5V | GND → GND
```

**LCD 1602 (4-bit mode)**
```
RS → D12 | E → D11 | D4 → D5 | D5 → D4 | D6 → D3 | D7 → D2
VSS → GND | VDD → 5V | V0 → Pot wiper | A → 5V | K → GND | RW → GND
```

**Buzzer** → D8 (+) / GND  
**Green LED** → D7 (with resistor)  
**Red LED** → A1 (with resistor)

## Setup Steps

1. Run Project 13 first and write down the real UID of your card.
2. Replace the example `authorizedUID` array in the sketch with your actual UID.
3. Install the **MFRC522** library (Servo and LiquidCrystal are built-in).
4. Upload and test.

## Adding More Cards

Extend the `checkUID()` function to compare against multiple stored UIDs, or store them in EEPROM for persistence.

## Possible Upgrades

- Add a keypad for PIN backup entry.
- Replace or supplement the servo with a relay-driven electric lock.
- Implement a master card that can enroll new users.
- Log access events over Serial or to an SD card.

This project is an excellent portfolio piece and a natural conclusion to the learning path.
