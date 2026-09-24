# 13 — RFID RC522 Basic Read

Read the unique identifier (UID) of RFID cards and key fobs.

## Description

The RC522 module operates at 13.56 MHz and communicates over SPI. Reading the UID is the first step toward any access-control application.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| RFID RC522 module | 1 |
| RFID cards / key fobs | 1+ |

## Wiring (Important: 3.3 V only!)

```
RC522          Arduino Uno
-----          -----------
SDA (SS)   --> D10
SCK        --> D13
MOSI       --> D11
MISO       --> D12
GND        --> GND
RST        --> D9
3.3V       --> 3.3V   ← Do NOT connect to 5 V
```

## Library

Install **MFRC522** via the Library Manager.

## Upload & Run

Open Serial Monitor (9600 baud). Bring a card close to the antenna. The UID will be printed in hexadecimal. Write it down — you will need it for the door-lock project.

## Next Step

Use the UID to decide whether to open a servo or activate a relay.
