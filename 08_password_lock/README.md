# 08 — Password Lock (Keypad)

Type a 4-digit code on a keypad — correct code grants access. The core
logic of every keypad door lock and safe.

## Real-world problem

Keypad locks collect digits into a buffer, compare it to a stored code
on `#`, and clear on `*`. This project is that exact state flow — plus
success/fail feedback — and it shows how a matrix keypad reads 16 keys
on only 8 wires.

## Learning objectives

- Drive a 4×4 matrix keypad with the **Keypad** library
- Accumulate input into a buffer and validate on a confirm key
- Give timed success/failure feedback without blocking (`millis()`)
- Understand row/column scanning (why 8 pins → 16 keys)

## Prerequisites

Project 03 (digital inputs), 06 (non-blocking timers help).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | 4×4 membrane keypad | 8-pin header: 4 rows + 4 cols |
| 1 | Buzzer | Feedback beeps |
| 1 | LED | Pin 13 = onboard works |

## Wiring

```
Keypad 8-pin header     Arduino
-------------------     -------
Row1–Row4           --> D9 D8 D7 D6   (in order)
Col1–Col4           --> D5 D4 D3 D2

Buzzer + --> D10     LED → D13 (onboard)
```

| Signal | Pins |
|--------|------|
| Keypad rows | D9, D8, D7, D6 |
| Keypad cols | D5, D4, D3, D2 |
| Buzzer / LED | D10 / D13 |

> Keypad pin order varies between clones — if keys decode wrong, swap the
> row/col arrays in the sketch, or check with a multimeter.

## Library

**Keypad** by Mark Stanley / Alexander Brevig (tested 3.1.1).

## How it works

1. The keypad has no chip — the library scans: it drives each row and
   reads the columns (that's why 4+4 pins cover 16 keys).
2. `getKey()` returns the pressed key's character, or `0` when idle —
   debouncing is handled inside the library.
3. Digits append to `input` (max 4); `#` compares `input == password`;
   `*` clears.
4. On success the LED lights for `GRANTED_MS` via `millis()` — the old
   version used `delay(1500)` which froze the keypad mid-flash.

## The algorithm

```
loop forever:
    if granted window expired → LED off
    key = keypad.getKey();  if none → continue
    if key == '#':
        input == password → GRANTED: LED on (GRANTED_MS), beep
        else              → DENIED: long low beep
        input = ""
    elif key == '*' → input = ""
    elif input.length() < 4 → input += key
```

## Upload & test

1. Upload `password-lock.ino`, Serial at 9600.
2. Type `1234` then `#` → `ACCESS GRANTED` + LED ~1.5 s + beep.
3. Wrong code + `#` → `WRONG PASSWORD` + long low beep.
4. `*` clears mid-typing. Change `password` in code and re-test.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Keys print as wrong characters | Row/col wire order ≠ arrays — match the table or swap arrays |
| No keys detected | Header reversed; or one row/col wire loose |
| Keys register twice | Jumper contact bounce on a wire — reseat it |
| Success but LED never turns off | `grantedUntil` handling was removed — restore the `millis()` check |

## Challenges

- **Beginner:** change the password and its length (update the `< 4` cap too).
- **Intermediate:** `*` deletes just the last digit instead of clearing everything; show `*` per typed digit on Serial.
- **Advanced:** lock out for 10 s after 3 wrong attempts — non-blocking, using the same timer pattern.

## Knowledge check

1. How does a 4×4 keypad read 16 keys on 8 wires?
2. Why is `#` handled differently from `*`?
3. What did `delay(1500)` break that the `millis()` window fixes?
4. Why does `input.length() < 4` exist — what bug does it prevent?

## Safety notes

- This is **not** a real security device — a 4-digit code over Serial,
  stored in plaintext, is a teaching demo. See project 11's security note.
