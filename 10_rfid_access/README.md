# 10 — RFID Access Control

Tap a card on an RC522 reader → green light and relay click if the card
is registered. The introduction to SPI peripherals and UID matching.

## Real-world problem

Access-control readers identify a card by its **UID** — a serial number
burned into the chip — and grant/deny access by comparing it to a
whitelist. This project does the full loop: detect → read UID → compare
→ timed grant feedback → log everything on Serial.

## Learning objectives

- Use **SPI** — the first shared peripheral bus (SCK/MOSI/MISO + per-chip CS)
- Read a MIFARE card UID with the **MFRC522** library
- Compare byte arrays, learn why `==` doesn't work on them
- Give timed feedback non-blockingly (the `millis()` window again)

## Prerequisites

Project 06 (non-blocking timers). Serial Monitor basics.

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | RFID-RC522 module + MIFARE card/keyfob | 3.3 V powered, SPI |
| 1 | LED + 220 Ω | Grant indicator |
| 1 | 5 V relay module (optional) | IN pin, low-latency "lock" stand-in |

## Wiring

```
RC522            Arduino
-----            -------
SDA (SS)     --> D10
SCK          --> D13        ← SPI clock, shared bus pin
MOSI         --> D11        ← SPI
MISO         --> D12        ← SPI
RST          --> D9
3.3V         --> 3.3V       ← NOT 5V — the RC522 is a 3.3 V part
GND          --> GND

LED:    D2 --[220Ω]--|-- GND
Relay:  IN --> D3, VCC --> 5V, GND --> GND
```

> **The SPI pins D11/D12/D13 are a shared bus** — this is why project 11
> had to move its LCD off those pins. Any second SPI device shares
> SCK/MOSI/MISO and only needs its own CS pin.

## Library

**MFRC522** by miguelbalboa (tested 1.4.12) — pulls in the `SPI` core.

## How it works

1. `PICC_IsNewCardPresent()` + `PICC_ReadCardSerial()` poll the field;
   on a card, `mfrc522.uid` gives the raw UID bytes.
2. `uidMatches()` loops both arrays byte-for-byte — C `==` compares
   pointers, never contents.
3. On a match: relay + LED turn on and a `GRANTED_MS` window opens; the
   `millis()` check in `loop()` closes it — the old version blocked for
   1.5 s inside `accessGranted()`.
4. Unknown cards deny, print their UID, and read `RELAY_MS` — keep the
   relay window short on a deny.

## The algorithm

```
loop forever:
    if now − grantedAt ≥ RELAY_MS → relay off, LED off
    if no new card → continue
    read uid;  print hex bytes
    if uidMatches(uid, ALLOWED_UID) → grant (relay+LED, timestamp)
    else → deny (short relay pulse, print UID)
    PICC_HaltA() + PCD_StopCrypto1() — required to re-detect
```

## Upload & test

1. Upload `10_rfid_access.ino`, Serial at 9600.
2. Tap your card → Serial prints its UID. If unknown: `ACCESS DENIED`.
3. Copy that printed UID into `ALLOWED_UID`, re-upload.
4. Tap again → `ACCESS GRANTED`, relay + LED for the window.
5. Rapid re-taps → each is a fresh event (no double-triggers while held).

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| `firmware version: 0x0` / init fails | 3.3 V not connected, or MOSI/MISO swapped |
| Card detected but wrong UID | Printed bytes are the *raw* UID — paste them into `ALLOWED_UID` exactly |
| Card only reads once | Missing `PICC_HaltA()`/`PCD_StopCrypto1()` — the PICC stays asleep |
| Relay chatters on card held near | Card re-presented every loop — the grant window + halt already cover this; check wiring |
| Works once then dead | Re-read after `StopCrypto1` requires a card to leave and re-enter the field — expected |

## Challenges

- **Beginner:** whitelist two UIDs — store them in a 2-D array and loop `uidMatches` over rows.
- **Intermediate:** lockout — deny all cards for 5 s after 3 consecutive unknown taps (non-blocking).
- **Advanced:** log grants/denials with timestamps, scroll them on an LCD (project 11's wiring).

## Knowledge check

1. Why does SPI need a per-device CS pin when SCK/MOSI/MISO are shared?
2. `uid == ALLOWED_UID` compiles but never works — what does `==` compare on arrays?
3. Why does the deny path use a shorter relay window than grant?
4. What do `PICC_HaltA()` and `PCD_StopCrypto1()` do, and why are both needed?

## Safety notes

> **This is a teaching demo, not real access control.** MIFARE UIDs are
> world-readable and trivially clonable — a "magic card" copies one in
> seconds. A production system authenticates the card's *contents*
> (cryptographic sector keys, DESFire, challenge-response), not just its
> serial number, and never exposes the whitelist over Serial. Also: the
> `ALLOWED_UID` is compiled into the firmware — anyone who reads your
> `.ino` knows the key.
