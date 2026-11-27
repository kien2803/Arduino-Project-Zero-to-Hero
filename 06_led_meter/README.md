# 06 — LED Light Meter (74HC595)

A light sensor drives an 8-LED bar graph — through **3 pins**, not 8.
Your first chip-to-chip communication: the shift register.

## Real-world problem

VU meters, battery indicators, volume bars — all show a level on a row
of LEDs. Driving 8 LEDs needs 8 pins… unless a 74HC595 converts 3
serial pins into 8 parallel outputs. This is the same trick that scales
to 7-segment displays, LED matrices, and relay boards.

## Learning objectives

- Use a 74HC595 shift register: `shiftOut`, latch, bit order
- Turn "8 outputs on 3 wires" into a reusable `writeLeds()` function
- Build a bar-graph pattern from a level (`(1 << level) - 1`)
- Sample a sensor non-blockingly with `millis()`

## Prerequisites

Project 02 (analog input), 04 (the LDR sensor itself).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | 74HC595 shift register | DIP-16 (kit part #9) |
| 8 | LEDs | Any colors |
| 8 | 220 Ω resistors | |
| 1 | LDR light sensor module | Kit part #8, analog out |

## Wiring

```
74HC595            Arduino         LDR module       Arduino
-------            -------         ----------       -------
DS  (14)       --> D2              VCC          --> 5V
SHCP(11)       --> D3              GND          --> GND
STCP(12)       --> D4              A0           --> A0
Q0–Q7 (15,1-7) --> LED anodes, each --[220Ω]-- GND
OE  (13)       --> GND  (outputs always enabled)
MR  (10)       --> 5V   (not reset)
VCC (16)       --> 5V
GND (8,13)     --> GND
```

| Signal | Pin |
|--------|-----|
| Data / Clock / Latch | D2 / D3 / D4 |
| LDR analog out | A0 |

## How it works

1. `shiftOut()` pushes 8 bits into the 595 one at a time (data + clock).
2. The LATCH pulse copies them to the outputs — all 8 LEDs update together.
3. The LDR's AO reads ambient light; 8 samples averaged kill jitter.
4. `map()` scales light → 0–8 level; `barPattern()` turns level N into
   `2^N − 1` (binary 00001111 = 4 LEDs lit).
5. Sampling is rate-limited by `millis()` — no `delay()`, the loop stays free.

## The algorithm

```
every 100 ms:
    light = average of 8 × analogRead(A0)
    level = constrain(map(light, 80, 900, 0, 8))
    writeLeds((1 << level) - 1)
```

## Upload & test

1. Upload `led-meter.ino`, Serial at 9600.
2. Cover the LDR → bar shrinks to 0–1 LEDs. Shine a torch → all 8.
3. Serial shows raw `light=` + `level=` — calibrate `CAL_LOW/CAL_HIGH`
   for your room if the range feels off.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| LEDs reversed (dark → full bar) | LDR orientation inverted — swap CAL_LOW/HIGH in the map |
| All LEDs stuck on/off | OE not on GND, or MR not on 5V — check pins 10 & 13 |
| Garbage patterns | Latch/clock swapped — verify D3=SHCP, D4=STCP |
| Level jitters between two bars | Increase `SAMPLES`, or add hysteresis (see Advanced) |

## Challenges

- **Beginner:** change the bar to a single moving dot — pattern `1 << level` instead.
- **Intermediate:** add a button that toggles bar ↔ dot display mode.
- **Advanced:** hysteresis — only change level when light crosses a threshold by ±30.

## Knowledge check

1. Why 3 pins instead of 8 — what does the latch pin actually do?
2. `MSBFIRST` vs `LSBFIRST` — which bit reaches Q7 first?
3. Why `(1 << level) - 1` — what binary number is level 5?
4. Could you chain a *second* 595 on the same 3 pins? Where does its data come from? (Hint: Q7S pin)

## Safety notes

- The 595 is a 5 V logic chip — safe everywhere here.
- Max ~8 mA per output with 220 Ω resistors — fine.
