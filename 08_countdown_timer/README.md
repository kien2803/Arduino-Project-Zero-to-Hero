# 08 — Countdown Timer (4-digit 7-segment)

A kitchen-style countdown: buttons set the minutes, a buzzer rings at
00:00. The hard new idea: **multiplexing** — 12 pins drive 32 segments.

## Real-world problem

Microwave timers, oven clocks, darkroom timers — all show MM:SS on
4-digit displays that cost far fewer pins than 32 segments suggest.
They light one digit at a time, ~250×/second, and persistence of
vision does the rest.

## Learning objectives

- Multiplex a common-cathode 4-digit display (digit select + segments)
- Run three things at once on `millis()`: display refresh, timer tick,
  button debounce — **zero** `delay()`
- A simple `SET → RUNNING → RINGING` state machine
- Why refresh rate matters (flicker vs. pin count)

## Prerequisites

Project 05 (single-digit patterns + debounce), 06 (`millis()` timing).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | 4-digit 7-segment display | **Common cathode** (kit part #10) |
| 8 | 220 Ω resistors | One per segment line |
| 2 | Push buttons | SET (+1 min) / START-PAUSE |
| 1 | Active buzzer | Kit part #34 |

## Wiring

```
Segments a,b,c,d,e,f,g,dp --> D2–D9  (each through 220Ω)
Digit cathodes  D1,D2,D3,D4 --> D10–D13
Button SET    --> A0 to GND      (INPUT_PULLUP)
Button START  --> A1 to GND      (INPUT_PULLUP)
Buzzer +      --> A2
```

| Signal | Pins |
|--------|------|
| Segments a–g + dp | D2–D9 |
| Digit enables | D10–D13 |
| Buttons / buzzer | A0 / A1 / A2 |

> Common **cathode**: a digit lights when its pin sinks LOW *and* its
> segments are driven HIGH — the opposite of project 05's common anode.

## How it works

1. Only **one digit is lit at a time** — `loop()` rotates through all
   four every 2 ms, so each digit is on 25 % of the time at ~125 Hz.
   Your eye blends it into a steady display.
2. `render()` turns `remainMs` into `MM:SS` patterns + a blinking colon.
3. The timer ticks 100 ms per `millis()` pass — independent of the
   display rotation.
4. Three states: `SET` (button adds minutes) → `RUNNING` (counts down,
   colon blinks) → `RINGING` (buzzer + flash, auto-resets after 5 s).

## The algorithm

```
every 2 ms:  blank current digit → light next digit (multiplex)
every 100 ms (RUNNING): remainMs -= 100 → render(MM:SS)
RINGING: buzzer toggles 200 ms, 5 s → back to SET
SET+BTN_SET: +60 s (cap 99:59)     BTN_START: SET↔RUNNING, or stop ring
```

## Upload & test

1. Upload `countdown-timer.ino`, Serial optional.
2. Shows `01:00`. Press SET → adds a minute each press (caps at 99:59).
3. Press START → counts down, colon blinks. Press again → pauses to SET.
4. At `00:00` → buzzer beeps + display flashes 5 s, then back to SET.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Only one digit ever lights | Digit enables not wired or all on one pin — check D10–D13 |
| Ghosting / faint wrong segments | Missing the "blank before switch" step in the multiplexer |
| Whole display flickers visibly | `DIGIT_MS` too high — keep ≤ 4 ms; or something else blocks the loop |
| Wrong digit order | Display's D1–D4 order ≠ assumed — swap the `DIG_PINS` array |
| Buzzer never stops | `RINGING` exit deleted — restore the 5 s `millis()` check |

## Challenges

- **Beginner:** start the default at `05:00` instead of `01:00`.
- **Intermediate:** START while SET resets to 00; long-press SET adds 10 min.
- **Advanced:** MM:SS → also show SS:hh (hundredths) — the display updates faster than the tick.

## Knowledge check

1. Why can't all four digits be lit at once on this wiring?
2. At `DIGIT_MS = 2`, what's each digit's duty cycle and the full-frame rate?
3. The colon blink uses `millis()/500` — why not a second timer variable?
4. Which two subsystems run "in parallel" in `loop()` — and what breaks if one used `delay()`?

## Safety notes

- Buzzer is polarized on some modules — check `+` if it stays silent.
- Segment resistors are required; 220 Ω each.
