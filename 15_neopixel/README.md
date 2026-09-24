# 15 — NeoPixel 12 LED RGB

Drive the 12-LED NeoPixel (WS2812) module with colorful effects.

## Description

NeoPixels are individually addressable RGB LEDs. Only one data pin is needed for the whole chain.

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Module LED Neo Pixel 12 LED RGB | 1 |

## Wiring

```
NeoPixel Module     Arduino
---------------     -------
DIN / Data      --> D6
VCC / +5V       --> 5V   (for 12 LEDs OK from Arduino; more LEDs need external supply)
GND             --> GND
```

## Library

Install **Adafruit NeoPixel** via Library Manager.

## Power note

12 LEDs at full white brightness can draw ~720 mA. The sketch limits brightness to 50. For longer strips always use external 5 V power supply and common ground.

## Upload & Run

You will see red → green → blue color wipes. Modify the `loop()` to create your own patterns.
