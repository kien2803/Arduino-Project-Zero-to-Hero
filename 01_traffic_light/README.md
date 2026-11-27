# 01 — Traffic Light

A 3-LED traffic light controller: the classic first Arduino program, built
like a real intersection light rather than a random blink.

## Real-world problem

Intersection traffic lights are just a microcontroller switching three
outputs on a fixed schedule. This project recreates that exact logic —
the same pattern used inside real traffic controllers (which simply have
more outputs and more states).

## Learning objectives

- Configure GPIO pins as outputs (`pinMode`, `digitalWrite`)
- Drive an LED safely through a current-limiting resistor
- Sequence behavior over time with `delay()`
- Store tunable values in named constants instead of magic numbers

## Prerequisites

None — this is the starting point of the course. You only need to know
how to upload a sketch (see the root [README](../README.md)).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno (or Nano / Nano Every) | Provides 5 V GPIO |
| 1 | Red LED (5 mm) | Forward voltage ≈ 2.0 V |
| 1 | Yellow LED (5 mm) | Forward voltage ≈ 2.0 V |
| 1 | Green LED (5 mm) | Forward voltage ≈ 2.1 V |
| 3 | Resistor 220 Ω, 1/4 W | ≈ 14 mA per LED |
| 1 | Breadboard + jumper wires | |

**Resistor sizing** — for Vcc = 5 V, Vled ≈ 2 V, I ≈ 14 mA:
`R = (5 V − 2 V) / 0.014 A ≈ 214 Ω` → use **220 Ω** (standard E12 value).

## Wiring

| Arduino pin | LED | LED cathode |
|-------------|-----|-------------|
| **D13** | Red — through 220 Ω to anode | → GND |
| **D12** | Yellow — through 220 Ω to anode | → GND |
| **D11** | Green — through 220 Ω to anode | → GND |

```
 ARDUINO UNO
┌────────────────┐
│             D13├───[220Ω]──►|──┐   RED
│             D12├───[220Ω]──►|──┤   YELLOW
│             D11├───[220Ω]──►|──┤   GREEN
│             GND├───────────┴───┴── GND rail (common cathode)
└────────────────┘
```

> **Simulation:** this project runs as-is in Wokwi/Tinkercad —
> 3 LEDs + 3 resistors on D13/D12/D11.

## How it works

`digitalWrite(pin, HIGH)` sources ~5 V on the pin → current flows through
the resistor → LED lights. `LOW` pulls the pin to 0 V → LED dark.
`setLights(r, y, g)` writes all three at once so exactly one LED is on.

The cycle is the state sequence of a real traffic light:

| Phase | LED | Duration | Meaning |
|-------|-----|----------|---------|
| 1 | Red | 5 s | Vehicles must **STOP** |
| 2 | Green | 4 s | Vehicles may **GO** |
| 3 | Yellow | 2 s | **Caution** / transition |

## The algorithm

```
loop forever:
    RED on, others off    → wait RED_MS
    GREEN on, others off  → wait GREEN_MS
    YELLOW on, others off → wait YELLOW_MS
```

`delay(ms)` blocks the CPU — acceptable here because the light does
nothing else. Later projects replace it with `millis()` timing.

## Upload & test

1. Upload `01_traffic_light.ino` (Arduino IDE, `./flash.sh`, or the
   [flasher app](../README.md#flashing-without-the-arduino-ide)).
2. The LEDs cycle red → green → yellow forever, no Serial needed.
3. Change `RED_MS`/`GREEN_MS`/`YELLOW_MS`, re-upload, observe the change.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| One LED never lights | LED backwards (long leg = anode) or missing resistor |
| All LEDs dim/flicker | Forgot the resistor or shared one between all three |
| Onboard "L" LED also blinks | Normal — D13 drives the onboard LED too |
| Timing looks wrong | Edited a `delay()` literal instead of the `*_MS` constants |

## Challenges

- **Beginner:** retune the timings to your local intersection's pattern; add a 4th "pedestrian red" LED that is on whenever green/yellow is off.
- **Intermediate:** replace `delay()` with a `millis()` state machine so the board stays responsive (same pattern used in projects 09 and 11).
- **Advanced:** add a pedestrian-request button on D2 — when pressed, finish the green phase early, blink green 3×, then go red.

## Knowledge check

1. Why is a resistor required in series with every LED?
2. What does `digitalWrite(pin, LOW)` do electrically to the pin?
3. If you changed all three `delay()` calls but the cycle didn't change, what did you probably miss?
4. Why is `delay()` a problem once a project must react to buttons at any time?

## Safety notes

- Always use a resistor with each LED — direct connection to 5 V will burn it.
- Do not exceed ~20 mA per GPIO pin (ATmega328P absolute max ≈ 40 mA).
