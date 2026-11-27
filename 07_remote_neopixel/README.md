# 07 — Remote NeoPixel Lamp

The 12-LED RGB ring controlled by the IR remote: on/off, colors,
brightness, and a spinning rainbow — one button at a time.

## Real-world problem

Smart bulbs take a remote and map each button to a color or mode.
This project is exactly that, minus Wi-Fi: the same IRremote decoding
as the old relay lamp, but the load is a WS2812 ring that needs its
own library and a data line.

## Learning objectives

- Drive a WS2812/NeoPixel ring with **Adafruit_NeoPixel**
- Reuse the IRremote v4 repeat-frame filter (`IRDATA_FLAGS_IS_REPEAT`)
- Map multiple remote buttons to a state (color/effect/brightness)
- Keep an animation running non-blockingly

## Prerequisites

Project 03 (Serial basics). The IR-repeat trap from the original
lesson 07 applies — read Troubleshooting before judging the remote.

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | 12-LED NeoPixel ring | WS2812 (kit part #12) |
| 1 | 1838T IR receiver | Kit part #14 |
| 1 | IR remote | Kit part #15 — 20-key NEC |
| 1 | 220 Ω resistor | On the ring's data line |

## Wiring

```
IR Receiver      Arduino       NeoPixel ring     Arduino
-----------      -------       -------------     -------
OUT          --> D11           DIN           --> D6 --[220Ω]
VCC          --> 5V            VCC/5V        --> 5V
GND          --> GND           GND           --> GND
```

## Library

- **IRremote** ≥ 4.x (`IrReceiver`, `decodedIRData`, `IS_REPEAT`)
- **Adafruit_NeoPixel** (tested 1.12.x) — `ring.fill`, `setPixelColor`,
  `ColorHSV`, `setBrightness`

## How it works

1. `IrReceiver.decode()` gives `protocol` + `command` per press;
   `IS_REPEAT` frames (button held) are dropped — same fix as the
   relay-flapping lesson.
2. Four commands drive lamp state: power toggle, next color, next
   effect, brightness step. **You must map your remote's codes first**
   (see below) — every remote's numbers differ.
3. `render()` draws the ring: solid color or a `ColorHSV` rainbow that
   a `millis()` timer advances every 80 ms — the loop never blocks.

## The algorithm

```
loop:
    if frame decoded and NOT repeat:
        print protocol + command            # for setup
        POWER  → toggle lampOn
        COLOR  → next palette color         EFFECT → solid/spin
        BRIGHT → next brightness step
        render()
    if lampOn and effect=spin and 80 ms elapsed → spinPos++, render()
```

## Upload & test

1. Upload `remote-neopixel.ino`, open Serial Monitor.
2. Press remote buttons — each prints `command=0xNN`.
3. Copy your buttons' codes into `CMD_POWER`/`CMD_COLOR`/`CMD_EFFECT`/
   `CMD_BRIGHT`, re-upload.
4. Power → ring lights; color/effect/brightness cycle on each press.
   Hold a button → **one** action (repeats filtered).

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Nothing decoded | IR out not on D11; remote not NEC — read `protocol=` |
| 2–3 actions per press | IRremote < 4.x, or `IS_REPEAT` check deleted |
| Wrong button acts | Codes differ — copy yours from Serial into `CMD_*` |
| Ring dark but Serial works | DIN wire missing, or DIN not on D6 |
| Colors swapped (red↔green) | Ring variant is GRB vs RGB — change `NEO_GRB` to `NEO_RGB` |

## Challenges

- **Beginner:** add a 6th color to `PALETTE`.
- **Intermediate:** long-press = smooth dimming (use the repeat count, not just filtering it out).
- **Advanced:** third effect — "theater chase" (one lit LED orbiting).

## Knowledge check

1. Why map your remote's codes instead of hardcoding one table forever?
2. `ring.fill(color)` vs a loop of `setPixelColor` — same result, which is clearer?
3. `ColorHSV` makes the rainbow trivial — what would it take with raw RGB?
4. Why does the spin animation live in `loop()` + `millis()` instead of `delay()`?

## Safety notes

- The ring is 5 V — safe. Full-white × 12 at full brightness ≈ 0.7 A;
  USB ports handle it, but for long runs dim it (`setBrightness` ≤ 120).
