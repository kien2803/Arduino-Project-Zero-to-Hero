# 04 — Automatic Night Light

An LED that switches itself on when the room gets dark — the same trick
as plug-in corridor night lights.

## Real-world problem

Corridor and porch night lights measure ambient light and switch at a
threshold. This project reads a light sensor's analog output, compares
it to a threshold, and drives the LED — including the real-world step of
*calibrating* the threshold for your room.

## Learning objectives

- Read a sensor's analog output (`analogRead`)
- Turn a continuous measurement into a binary decision (thresholding)
- Calibrate a threshold against real sensor output via Serial Monitor
- Tell apart a module's **AO** (proportional) and **DO** (comparator) outputs

## Prerequisites

Project 02 (`analogRead`).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | 4-pin light sensor module (MS-CDS05 style, LDR + LM393) | Has AO **and** DO pins |
| 1 | LED + 220 Ω resistor | |
| — | Jumper wires | |

**About the two outputs:** the module's *AO* pin gives the raw
light-dependent voltage (0–1023 after `analogRead`). Its *DO* pin is a
digital HIGH/LOW switched by an onboard comparator + blue trim-pot.
**This project uses AO** — you see the actual numbers, which makes
calibration visible and teaches thresholding. (DO is covered as an
extension below.)

## Wiring

```
Light sensor (4-pin)     Arduino
--------------------     -------
VCC                  --> 5V
GND                  --> GND
AO                   --> A0
DO                   --> (not connected)

LED anode  --> 220 Ω --> D9
LED cathode ----------> GND
```

| Signal | Arduino pin |
|--------|-------------|
| Sensor AO | **A0** |
| LED anode (via 220 Ω) | **D9** |

> **Simulation:** Wokwi has an LDR module; set it up on A0 the same way.

## How it works

1. The LDR changes resistance with light; the module turns it into a
   voltage on AO (on most modules: dark → *higher* reading).
2. `analogRead(A0)` → 0–1023, printed to Serial every 300 ms.
3. `lightValue > threshold` → dark → LED on; otherwise LED off.
4. `threshold = 900` is a starting guess — you will tune it for your room.

## The algorithm

```
loop forever:
    lightValue = analogRead(A0)
    print lightValue
    if lightValue > threshold → LED on   ("DARK")
    else                      → LED off  ("BRIGHT")
    wait 300 ms
```

## Upload & test

1. Upload `night-light.ino`, open Serial Monitor at 9600.
2. Watch the numbers in normal room light — write down the typical value.
3. Cover the sensor — the number should jump past `threshold` → LED on.
4. **Calibrate:** set `threshold` a bit above your room's "bright" value
   and below the covered value, re-upload, verify it flips cleanly.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| LED on in bright light, off when covered | Your module's AO is inverted (bright → high) — flip `>` to `<` |
| Value stuck at 0 or 1023 | AO not connected / wired to wrong pin |
| LED chatters at the boundary | Normal — needs hysteresis (see Challenges) |
| Nothing in Serial Monitor | Wrong baud (must be 9600) or board not flashed |

## Challenges

- **Beginner:** find your room's bright and dark values, write your calibrated `threshold` in the code comment.
- **Intermediate:** add hysteresis — separate `DARK_ON = 800` and `BRIGHT_OFF = 700` thresholds so the LED can't flicker at the boundary.
- **Advanced:** wire the module's **DO** pin to D2 and compare both approaches in one sketch — when would you prefer DO over AO?

## Knowledge check

1. What's the difference between the module's AO and DO pins?
2. Why is calibrating `threshold` against *your* sensor output better than trusting the example value?
3. The LED flickers when light hovers at the threshold — what technique fixes that?
4. If your module outputs *lower* values when dark, what exactly must change in the code?

## Safety notes

- Sensor modules vary in AO polarity — verify with Serial before trusting
  the `>` comparison; flipping it is a one-character fix, not an error.
