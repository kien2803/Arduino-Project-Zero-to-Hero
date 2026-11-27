# 02 — Dimmer Lamp (Potentiometer)

Control LED brightness with a knob — the core of every dimmer lamp,
volume control, and adjustable desk light.

## Real-world problem

A desk lamp with a brightness knob reads an analog position and converts
it to light intensity. Real dimmers use the same idea: an analog control
voltage → a proportional output (PWM duty cycle in our case, TRIAC phase
control in mains dimmers).

## Learning objectives

- Read an analog voltage with `analogRead()` (10-bit ADC, 0–1023)
- Wire a potentiometer as a variable voltage divider
- Dim an LED with `analogWrite()` PWM on a `~` pin
- Rescale values between ranges with `map()`

## Prerequisites

Project 01 (GPIO outputs, LED + resistor, uploading a sketch).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno / Nano | Any ATmega328P board |
| 1 | LED | Any color |
| 1 | 220 Ω resistor | Current limit for LED |
| 1 | Potentiometer | 10 kΩ linear taper |
| — | Breadboard + jumper wires | |

## Wiring

```
                +5V
                 |
                [POT]   10 kΩ — outer pins to 5V and GND
                 |        wiper (middle pin) → A0
                 +----------> A0
                 |
                GND

  D9 ----[220 Ω]---->|---- GND   (LED anode through resistor)
```

| Signal | Arduino pin |
|--------|-------------|
| Pot wiper | **A0** |
| LED anode (via 220 Ω) | **D9** (PWM `~`) |

> **Simulation:** runs as-is in Wokwi/Tinkercad.

## How it works

1. The potentiometer is a divider: the wiper voltage sweeps 0–5 V.
2. `analogRead(A0)` returns a **10-bit** value 0–1023 proportional to it.
3. `map(potValue, 0, 1023, 0, 255)` scales it to the **8-bit** PWM range.
4. `analogWrite(9, brightness)` emits a ~490 Hz PWM square wave; the LED's
   average brightness follows the duty cycle.

```mermaid
flowchart LR
  POT["A0<br/>potentiometer"] -->|analogRead<br/>0–1023| MCU{{"Arduino"}}
  MCU -->|analogWrite<br/>0–255| PWM["D9 ~PWM"]
  PWM --> R["220 Ω"] --> LED["LED"] --> GND[("GND")]
```

## The algorithm

```
loop forever:
    potValue  = analogRead(A0)        // 0..1023
    brightness = map(potValue → 0..255)
    analogWrite(D9, brightness)
```

## Upload & test

1. Upload `dimmer-led.ino`.
2. Turn the pot slowly — brightness tracks the knob in real time.
3. Optional: add `Serial.begin(9600)` + `Serial.println(brightness)` to
   watch the raw values (see the Challenges).

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| LED only on/off, no dimming | Wired to a non-PWM pin — must be a `~` pin |
| Brightness inverted | Pot outer pins swapped 5V/GND — harmless, flip them |
| Jumpy/flickery at low values | ADC noise — average several reads (challenge below) |
| LED never fully off | Residual duty <1% — treat brightness < 5 as 0 |

## Challenges

- **Beginner:** add the Serial monitor prints and write down the raw `potValue` where the LED visibly turns on.
- **Intermediate:** smooth the reading with an 8-sample average or `potValue = (potValue*3 + analogRead(A0))/4` exponential filter.
- **Advanced:** raise the PWM frequency on pin 9 via `TCCR1B` (Timer1 prescaler) and hear/see the difference on an oscilloscope or camera.

## Knowledge check

1. Why must the LED be on a `~` (PWM-capable) pin instead of any digital pin?
2. `analogRead` is 10-bit and `analogWrite` is 8-bit — what does `map()` do about that?
3. The pot is connected 5V–GND–A0. What circuit is it, and what voltage does the wiper produce?
4. Why does the LED appear steady even though it's really flashing 490×/s?

## Safety notes

- A pot wired wrong (wiper to GND, ends to pin) can short the pin — double-check before powering.
- Keep the 220 Ω resistor in series with the LED.
