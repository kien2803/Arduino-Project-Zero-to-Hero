# 10 — RFID Access Control (RC522 + NeoPixel)

Tap a card → a **green sweep** on the ring and the relay clicks open.
Unknown card → **red flash**. Same access-control lesson, now with a
proper status display instead of a bare LED.

## Real-world problem

Badge readers don't just open a door — they *show* the result. This
project keeps the core (SPI card reader, UID whitelist, timed grant)
and adds the feedback layer real readers have: a NeoPixel ring that
spins green on success and blinks red on denial.

## Learning objectives

- SPI bus: SCK/MOSI/MISO shared + per-device CS (SS)
- Read a MIFARE UID with **MFRC522**, match against a whitelist
- Reuse the NeoPixel as a *status* output (not just a lamp)
- `millis()`-timed grant — the loop never blocks

## Prerequisites

Projects 07 (NeoPixel basics), 06 (`millis()` timing). SPI is new —
that's the point.

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | RFID-RC522 + MIFARE card/fob | 3.3 V, SPI (kit part #2) |
| 1 | 12-LED NeoPixel ring | Kit part #12 |
| 1 | 5 V relay module | Kit part #4 |
| 1 | 220 Ω resistor | Ring data line |

## Wiring

```
RC522            Arduino         NeoPixel        Arduino
-----            -------         --------        -------
SDA (SS)     --> D10             DIN         --> D7 --[220Ω]
SCK          --> D13   ← SPI     VCC         --> 5V
MOSI         --> D11   ← SPI     GND         --> GND
MISO         --> D12   ← SPI
RST          --> D9              Relay IN    --> D2
3.3V         --> 3.3V  (NOT 5V)  Relay VCC   --> 5V, GND --> GND
GND          --> GND
```

| Signal | Pin | Note |
|--------|-----|------|
| RC522 SS / RST | D10 / D9 | |
| SPI SCK / MOSI / MISO | D13 / D11 / D12 | shared bus |
| Relay / NeoPixel | D2 / D7 | |

## Libraries

**MFRC522** (1.4.x), **Adafruit_NeoPixel** (1.12.x) — see `platformio.ini`.

## How it works

1. `PICC_IsNewCardPresent()` + `PICC_ReadCardSerial()` poll the field;
   `rfid.uid` carries the raw bytes.
2. `uidMatches()` compares byte-by-byte — `==` on arrays compares
   pointers, never contents.
3. Three states (`IDLE`/`GRANTED`/`DENIED`), each with its own
   `millis()` exit timer — the loop keeps polling new cards the whole
   time, no `delay()`.
4. The ring *is* the feedback: green sweep while open, red blink on
   deny — so a state change is visible across the room.

## The algorithm

```
loop:
    GRANTED expired → relay off, ring clear, IDLE
    DENIED  expired → ring clear, IDLE
    animate ring per state
    new card? → read UID → print → GRANTED (match) or DENIED
    halt + stopCrypto (required to see the next card)
```

## Upload & test

1. Upload `rfid-access.ino`, Serial at 9600.
2. `RC522 firmware: 0x…` — anything but `0x0` means SPI talks.
3. Tap a card → UID prints, `ACCESS DENIED` + red flash.
4. Paste the UID into `ALLOWED_UID`, re-upload, tap again →
   green sweep + relay ~3 s.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| `firmware: 0x0` | RC522 powered at 5 V or SPI miswired — it's a **3.3 V** part |
| Card reads once only | `PICC_HaltA`/`StopCrypto1` removed — restore them |
| Wrong card grants | `ALLOWED_UID` bytes pasted wrong — copy Serial output exactly |
| Relay clicks, ring dark | DIN on wrong pin (D7) or `NEO_GRB` mismatch |
| Relay stays on | Grant-window `millis()` exit deleted — restore it |

## Challenges

- **Beginner:** two UIDs in `ALLOWED_UID` — a 2-D array + row loop.
- **Intermediate:** third state `LOCKOUT` — deny all taps 5 s after 3 bad cards.
- **Advanced:** log each tap's UID + grant/deny to Serial with timestamps.

## Knowledge check

1. Why does SPI need a separate SS pin per device when SCK/MOSI/MISO are shared?
2. `uid == ALLOWED_UID` compiles but never works — what does `==` compare on arrays?
3. Why is the deny window shorter than the grant window?
4. What do `PICC_HaltA()` + `PCD_StopCrypto1()` do — why both?

## Safety notes

> **Not real access control.** MIFARE UIDs are world-readable and
> clonable; a "magic card" copies one in seconds. Real systems
> authenticate card *contents* (crypto keys, DESFire), not the serial
> number — and never print the whitelist over Serial. The `ALLOWED_UID`
> also lives in the firmware: anyone reading the sketch has the key.
