# 05 — Digital Dice

Press a button → the 7-segment display shuffles and lands on a number
1–6. Your first display project: how a digit is just 7 LEDs in disguise.

## Real-world problem

Board-game dice, random counters, and cheap handheld games all show one
digit on a 7-segment display. Behind it: a lookup table of which
segments to light for each number — the same trick real displays use.

## Learning objectives

- Drive a 1-digit 7-segment display directly from GPIO pins
- Encode digits as bit patterns in an array
- Use `random()` properly (seed it, bound it)
- Debounced button input + a short "rolling" animation state

## Prerequisites

Projects 01 (digital output), 03 (buttons + `INPUT_PULLUP`).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | 1-digit 7-segment display | **Common anode** (kit part #13) — ON = pin LOW |
| 7 | 220 Ω resistors | One per segment — required |
| 1 | Push button | 4-pin tactile |

## Wiring

```
7-seg pins     Arduino        (common anode → 5V)
a          --> D2 --[220Ω]
b          --> D3 --[220Ω]
c          --> D4 --[220Ω]
d          --> D5 --[220Ω]
e          --> D6 --[220Ω]
f          --> D7 --[220Ω]
g          --> D8 --[220Ω]
COM (2x)   --> 5V

Button between D9 and GND (internal pull-up)
```

> **Common anode** means the shared pin goes to 5V and each segment
> lights when its pin is driven **LOW** — inverted logic, handled in
> `showDigit()`. If your display is common *cathode*, COM goes to GND
> and you flip the LOW/HIGH in that function.

## How it works

1. Each digit 1–6 is a 7-bit pattern: bit 0 = segment a … bit 6 = g.
   `DIGITS[]` stores the table; `showDigit(n)` walks the bits.
2. `pressed()` returns true **once** per debounced press.
3. A press starts a 600 ms "rolling" state — faces flicker by every
   60 ms — then a final `random(1, 7)` result stays lit.
4. `randomSeed(analogRead(A0))`: noise on the floating analog pin gives
   each power-up a different sequence.

## The algorithm

```
loop:
    if pressed and not rolling → rolling = true, rollStart = now
    while rolling:
        every 60 ms → showDigit(random face)      # flicker
        after 600 ms → show final random digit, print it
```

## Upload & test

1. Upload `digital-dice.ino`, Serial at 9600 (optional).
2. Press → digits flicker ~0.6 s → settles on 1–6, printed on Serial.
3. Press rapidly → only one roll at a time (state guard works).
4. Hold the button → single roll (edge detection, not level).

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Segments lit wrong / garbled | Segments wired out of order — re-check a–g |
| Display inverted (lit where it shouldn't) | Common **cathode** display — flip LOW/HIGH in `showDigit` |
| Same sequence every reset | `randomSeed` removed — the A0 pin must be floating |
| One press → many rolls | Debounce broken — check `stable`/`changed` logic |

## Challenges

- **Beginner:** change the dice to 0–9 (add patterns to `DIGITS`).
- **Intermediate:** two dice — second display on A1–A5 + D10/D11 (mind the pins).
- **Advanced:** roll animation that *decelerates* — flicker gap grows from 40→200 ms before settling.

## Knowledge check

1. Why does a common-anode display turn a segment ON with LOW?
2. What does `random(1, 7)` return — why 7 and not 6?
3. Why seed `random()` — what happens without it on a real die game?
4. In `pressed()`, what two variables distinguish "held" from "new press"?

## Safety notes

- Never wire a segment without its 220 Ω resistor — it'll draw too much current.
