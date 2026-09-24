# 13 — RFID RC522 Basic Read

Read the unique ID (UID) of the RFID cards / tags included in the kit.

## Description

The RC522 module works at 13.56 MHz and communicates via SPI. This is the foundation for access-control projects (door lock, attendance, etc.).

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Module RFID RC522 | 1 |
| 1 | RFID Card + Keyfob | 1+ |

## Wiring (important: 3.3 V!)

```
RC522          Arduino UNO
-----          -----------
SDA (SS)   --> D10
SCK        --> D13
MOSI       --> D11
MISO       --> D12
GND        --> GND
RST        --> D9
3.3V       --> 3.3V   << DO NOT use 5V
```

## Library

Install **MFRC522** by GithubCommunity / miguelbalboa via Library Manager.

## Upload & Run

Open Serial Monitor (9600). Bring a card close to the antenna. You will see the UID in HEX. Write it down — you will need it for the door-lock project.

## Next

Use the UID to decide whether to open a servo / activate a relay.
