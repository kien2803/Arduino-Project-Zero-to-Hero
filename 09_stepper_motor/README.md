# 09 — Stepper Motor (28BYJ-48 + ULN2003)

Turn a pot → the motor spins faster/slower; press a button → it
reverses. Your first *positioned* motor: one that moves in steps.

## Real-world problem

Printers, scanners, camera focus rings — anywhere exact positioning
matters, steppers win over DC motors because you count steps instead
of measuring position. The 28BYJ-48 is the classic learning stepper:
cheap, 5 V, gearbox-reduced to ~2048 steps/rev.

## Learning objectives

- Why a stepper needs a driver (ULN2003) — GPIO can't power coils
- Half-step sequencing: 8 phases for smooth motion
- Convert a pot reading into step *timing*, not PWM
- `micros()` for sub-millisecond timing

## Prerequisites

Project 02 (pot → analog input), 03 (button).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | 28BYJ-48 stepper | Kit part #17 |
| 1 | ULN2003 driver board | Bundled with the 28BYJ-48 |
| 1 | B10K potentiometer | Kit part #29 |
| 1 | Push button | |

## Wiring

```
ULN2003 board    Arduino         Pot              Arduino
------------     -------         ---              -------
IN1          --> D8              outer pins   --> 5V / GND
IN2          --> D9              wiper        --> A0
IN3          --> D10
IN4          --> D11             Button --> D2 to GND (INPUT_PULLUP)
+            --> 5V
-            --> GND
```

| Signal | Pin |
|--------|-----|
| Coils IN1–IN4 | D8–D11 |
| Pot wiper | A0 |
| Direction button | D2 |

## How it works

1. The motor has 4 coils; energizing them **in sequence** drags the
   shaft one step at a time. `PHASES[8]` is the half-step table —
   smooth, ~half the step angle.
2. Each `loop()` pass checks: has `stepGap` elapsed? If yes, advance
   `phase` by `direction` and write the coils. `micros()` times it —
   the gap is as small as ~1 ms.
3. The pot maps to the inter-step gap (fast ↔ slow); the button
   flips `direction`.
4. No `delay()` anywhere — the loop stays free for the button.

## The algorithm

```
loop:
    if button → direction = -direction
    stepGap = map(pot, 0,1023, 20 ms, 0.9 ms)
    if micros() - lastStep >= stepGap:
        phase += direction (wraps 0..7)
        write coils from PHASES[phase]
```

## Upload & test

1. Upload `stepper-motor.ino`, Serial at 9600.
2. Motor spins slowly. Turn the pot → speeds up.
3. Press the button → direction flips, printed on Serial.
4. Pot hard right → near-max speed (may stall at extremes — normal for
   this cheap motor).

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Motor hums, doesn't turn | Coil order wrong — swap IN1–IN4 until it steps cleanly |
| Turns only one direction | `direction` logic broken — check the wrap-around `+8` |
| Jitters / random jumps | Power sag — give the ULN2003 its own 5 V, share grounds |
| No motion at all | ULN2003's `+`/`-` not powered; or 28BYJ-48 plug on wrong pins |

## Challenges

- **Beginner:** map the pot to a fixed set of speeds (3 gears: slow/med/fast) instead of continuous.
- **Intermediate:** second button = "go to position 0" — counts steps home.
- **Advanced:** acceleration — ramp `stepGap` from slow to fast over 200 steps (real stepper drivers do this).

## Knowledge check

1. Why can't you drive the coils directly from GPIO pins?
2. Full-step vs half-step — what does the 8-phase table buy you?
3. `micros()` vs `millis()` — why does this project need the finer one?
4. The `(phase + direction + 8) % 8` trick — what problem does `+8` solve?

## Safety notes

- The ULN2003 chip warms up under load — normal, don't hold it.
- Don't power the stepper from USB and a 9 V battery at once.
