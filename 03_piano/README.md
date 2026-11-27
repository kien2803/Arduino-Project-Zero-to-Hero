# 03 — Mini Piano (Buzzer + Pushbuttons)

Four buttons, four notes — the same idea as a toy piano or a doorbell
with selectable chimes.

## Real-world problem

Doorbells, toy pianos, and microwave keypads all map "button → sound".
This project builds that mapping: each button plays a musical note on a
piezo buzzer while held.

## Learning objectives

- Read pushbuttons with `INPUT_PULLUP` (active-LOW logic)
- Generate tones with `tone()` / `noTone()`
- Understand why only one button can win in an `else if` chain
- Map physical inputs to frequencies (Hz)

## Prerequisites

Project 01 (digital I/O basics).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno / Nano | |
| 1 | Passive buzzer (piezo) | **Not** an active buzzer — see notes |
| 4 | Pushbuttons | Momentary tactile switches |
| — | Breadboard + jumper wires | |

> **Passive vs active buzzer:** an *active* buzzer makes its own tone when
> powered — `tone()` can't change its pitch. A *passive* buzzer is just a
> speaker — the Arduino must generate the waveform. You need passive here.

## Wiring

```
  D2 ----[BUTTON]---- GND      (Do)
  D3 ----[BUTTON]---- GND      (Re)
  D4 ----[BUTTON]---- GND      (Mi)
  D5 ----[BUTTON]---- GND      (Sol)

  D9 ----> BUZZER+ ----> GND
```

| Button | Pin | Note | Frequency |
|--------|-----|------|-----------|
| Do | D2 | C4 | 262 Hz |
| Re | D3 | D4 | 294 Hz |
| Mi | D4 | E4 | 330 Hz |
| Sol | D5 | G4 | 392 Hz |
| Buzzer | D9 | — | — |

Buttons use the internal `INPUT_PULLUP` resistor — **no external
resistors needed**. Idle pin = HIGH; pressed pin = LOW.

> **Simulation:** runs as-is in Wokwi/Tinkercad (piezo supported).

## How it works

1. `INPUT_PULLUP` holds each button pin at 5 V through ~20–50 kΩ.
2. Pressing connects the pin straight to GND → reads `LOW` (active-LOW).
3. `tone(buzzerPin, freq)` outputs a square wave at that frequency.
4. The `else if` chain picks the **first** pressed button; with nothing
   pressed, `noTone()` silences the buzzer.

## The algorithm

```
loop forever:
    if      Do  pressed → tone(262)
    else if Re  pressed → tone(294)
    else if Mi  pressed → tone(330)
    else if Sol pressed → tone(392)
    else                → noTone()
```

## Upload & test

1. Upload `piano.ino`.
2. Press each button — its note sounds while held, stops on release.
3. Press two buttons at once — only the *first* in the chain plays.
   (Why? See Knowledge check.)

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Buzzer silent | Active buzzer instead of passive; or +/- swapped |
| Note keeps playing after release | Button wired to 5V instead of GND (need pull-DOWN) — rewire to GND |
| Random triggering | `INPUT` used instead of `INPUT_PULLUP` — floating pin |
| Wrong button plays | Buttons mapped to different pins than the table |

## Challenges

- **Beginner:** add a 5th note (Fa 349 Hz on D6, La 440 Hz on D7) for a full pentatonic scale.
- **Intermediate:** store pins+notes in arrays and loop over them instead of the `else if` chain — adding a note becomes a one-line change.
- **Advanced:** play a melody: `int notes[] = {262,294,330,...}; int beats[] = {4,4,8,...};` + `tone(pin, notes[i], beat)` — a song player.

## Knowledge check

1. Why do the buttons read `LOW` when pressed instead of `HIGH`?
2. What removes the need for an external pull-up resistor per button?
3. Pressing Do and Sol together plays only Do — which language feature causes that?
4. Why can't `tone()` control an *active* buzzer's pitch?

## Safety notes

- Buttons connect pins directly to GND — that's fine **because** the pins
  are inputs with pull-ups. Never wire a button between a pin configured
  `OUTPUT`/`HIGH` and GND.
