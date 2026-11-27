# 06 — Anti-Theft Vibration Alarm

A shock sensor + buzzer + LED — the basic alarm in drawer alarms, bike
alarms, and "do not touch" gadgets.

## Real-world problem

Simple security alarms detect movement of the protected object and sound
a warning. This project detects a shock on a vibration sensor's digital
output and raises a timed alert — the alarm stays active briefly instead
of chattering on/off with the sensor.

## Learning objectives

- Read a sensor module's digital (DO) output
- Detect a *rising edge* of an event, not just its level
- Hold an alarm active for a timed window with `millis()` — no `delay()`
- See why naive `delay()`-as-debounce blocks the loop

## Prerequisites

Project 03 (digital inputs). Helpful: project 04's AO-vs-DO note.

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | Vibration / shock sensor module | SW-420/SW-18020 style; DO output |
| 1 | Buzzer | Active or passive — short `tone()` burst |
| 1 | LED (optional) | Pin 13 = onboard LED works |

## Wiring

```
Vibration Sensor     Arduino
----------------     -------
VCC              --> 5V
GND              --> GND
DO               --> D2

Buzzer +         --> D8
Buzzer -         --> GND
```

| Signal | Arduino pin |
|--------|-------------|
| Sensor DO | **D2** |
| Buzzer + | **D8** |
| Alarm LED | **D13** (onboard) |

Turn the module's trim-pot until DO stays LOW while the desk is still.

## How it works

1. The module's DO pulses HIGH briefly on each shock.
2. The sketch detects the **rising edge** (`LOW → HIGH`), not the level —
   one shock = one alert event even if DO stays high a while.
3. On a shock: a 300 ms beep starts (`tone(pin, freq, duration)` runs in
   hardware — non-blocking) and an alarm window opens (`ALARM_MS`).
4. The LED stays on for the whole window; a new shock **extends** it.
   `millis()` does the timing — `loop()` never blocks.

## The algorithm

```
loop forever:
    vib = digitalRead(D2)
    if vib rising edge:
        alarmUntil = now + ALARM_MS
        beep 300 ms
        log "Vibration detected!"
    LED = (now < alarmUntil)
```

## Upload & test

1. Upload `06_anti_theft_alarm.ino`, Serial at 9600 (optional).
2. Tap the sensor lightly → beep + LED on ~1.5 s + console message.
3. Tap repeatedly → each tap re-arms the window; LED stays on continuously.
4. Desk still → LED off, no messages.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Alarm never triggers | Trim-pot too insensitive — turn slowly while tapping |
| Alarm triggers constantly / on its own | Trim-pot too sensitive — back it off until idle DO reads LOW |
| LED stuck on | Sensor DO wired to an INPUT_PULLUP line noise — check the DO wire is on D2 |
| Long buzzes instead of short beeps | The `tone()` duration is hardware-timed — if you edited it, keep the duration arg |

## Challenges

- **Beginner:** change `ALARM_MS` and feel the difference between edge-triggering and level-triggering.
- **Intermediate:** count shocks — ignore a single tap, alarm only after 3 shocks within 5 s (still non-blocking).
- **Advanced:** two-level alarm — short beep warning on the first shock, continuous alarm after the third (state machine like project 09).

## Knowledge check

1. Why detect the *edge* of DO instead of just `if (vib == HIGH)`?
2. `tone(pin, freq, duration)` doesn't block — where does the timing actually happen?
3. What does `millis() < alarmUntil` replace in the naive version of this sketch?
4. Why does a repeated shock keep the LED on instead of retriggering it off/on?

## Safety notes

- The sensor DO output is 5 V logic — safe to wire directly.
- If you later drive a loud siren, use a relay/transistor — never power it from a GPIO pin.
