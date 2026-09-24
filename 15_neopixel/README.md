# 15 — NeoPixel (12 LED RGB)

Drive a 12-LED NeoPixel (WS2812) module with simple color effects.

## Description

NeoPixels are individually addressable RGB LEDs. Only one data pin is required for the entire chain.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| NeoPixel / WS2812 module (12 LEDs) | 1 |

## Wiring

```
NeoPixel Module     Arduino
---------------     -------
DIN / Data      --> D6
VCC / +5V       --> 5V
GND             --> GND
```

## Library

Install **Adafruit NeoPixel** via the Library Manager.

## Power Note

Twelve LEDs at full white brightness can draw several hundred milliamps. The example limits brightness to a safe level. For longer strips always use an external 5 V supply and connect the grounds together.

## Upload & Run

You will see sequential red, green, and blue color wipes. Modify the `loop()` function to create your own patterns.
