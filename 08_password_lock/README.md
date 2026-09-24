# 08 — Password Lock (Keypad)

A simple electronic lock that opens only when the correct 4-digit password is entered.

## What it does

- Type a 4-digit code on the keypad.
- Press `#` to confirm.
- Correct password → green feedback (LED + short beep).
- Wrong password → long low beep.
- Press `*` to clear and start over.

This is the core logic of almost every keypad door lock and safe.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| 4×4 keypad | 1 |
| Buzzer | 1 |
| LED | 1 |

## Wiring

```
Keypad (typical)     Arduino
----------------     -------
Rows 1-4         --> D9 D8 D7 D6
Cols 1-4         --> D5 D4 D3 D2

Buzzer + --> D10
LED      --> D13 (with resistor if external)
```

## Library

Install **Keypad** by Mark Stanley / Alexander Brevig.

## Upload & Test

1. Upload the sketch.
2. Open Serial Monitor.
3. Type `1234` then `#` → you should see “ACCESS GRANTED”.
4. Change the password in the code to anything you like.

## Extensions

- Add a servo to actually open a latch.
- Show asterisks on an LCD while typing.
- Limit the number of wrong attempts.
