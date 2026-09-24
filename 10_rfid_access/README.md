# 10 — RFID Access Control

A basic card-based access system. Only the authorized RFID card is accepted.

## What it does

- Scan a card.
- If the UID matches the stored authorized UID → success beep + LED on for 2 seconds.
- If the UID is unknown → long error beep.

This is the foundation of every RFID door reader, attendance system, and access panel.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| RFID RC522 module | 1 |
| RFID cards / key fobs | 1+ |
| LED + buzzer | 1 each |

## Wiring (RC522 must use 3.3 V!)

```
RC522          Arduino
-----          -------
SDA        --> D10
SCK        --> D13
MOSI       --> D11
MISO       --> D12
RST        --> D9
3.3V       --> 3.3V
GND        --> GND
```

## Important first step

1. Upload this sketch with any UID.
2. Open Serial Monitor and scan your card.
3. Copy the printed UID into the `authorizedUID` array.
4. Upload again.

## Library

Install **MFRC522**.

## Extensions

- Store several authorized UIDs.
- Add a servo to open a real latch (see next project).
- Show messages on an LCD.
