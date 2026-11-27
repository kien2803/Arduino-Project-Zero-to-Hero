# Recommended Components

This series is designed around the kit pictured in
[docs/kit-contents.png](./docs/kit-contents.png) — a standard Arduino
Uno starter kit. You do not need every part for every project.

## Essential

| Category | Items |
|----------|-------|
| Board | Arduino Uno R3 (or compatible) |
| Power | USB cable, 9 V battery + DC-jack clip |
| Prototyping | Breadboard, jumper wires (M-M + F-M) |
| Basic | Red/green/yellow LEDs, 220 Ω / 1 kΩ / 10 kΩ resistors, push buttons, B10K potentiometer, active buzzer |

## Sensors & Input

| Item | Used in projects |
|------|------------------|
| Light sensor (LDR module) | 04 Night Light, 06 LED Meter |
| IR receiver + 20-key remote | 07 NeoPixel Lamp, 11 Smart Door Lock |
| RFID RC522 + cards/tags | 10 RFID Access, 11 Smart Door Lock |

## Displays & Output

| Item | Used in projects |
|------|------------------|
| 1-digit 7-segment (common anode) | 05 Digital Dice |
| 74HC595 shift register + 8 LEDs | 06 LED Meter |
| 12-LED NeoPixel ring (WS2812) | 07 Remote Lamp, 10 RFID, 11 Door Lock |
| 4-digit 7-segment (common cathode) | 08 Countdown Timer |
| LCD 1602 | 11 Smart Door Lock |
| SG90 servo | 11 Smart Door Lock |
| 28BYJ-48 stepper + ULN2003 driver | 09 Stepper Motor |
| 1-channel 5 V relay | 10 RFID Access |

## Kit contents reference

The numbered photo in `docs/kit-contents.png` maps to: Uno R3, RC522 +
tags, LCD1602, 1-ch relay, NTC module, SW-420 vibration module, LDR
module, 74HC595, 4-digit 7-seg, 12-LED NeoPixel ring, 1-digit 7-seg,
1838T IR receiver, 20-key remote, SG90, 28BYJ-48 + ULN2003, jumpers,
F-M dupont, 9 V battery clip + battery, button caps + buttons, kit box,
yellow/green/red LEDs, B10K pot, breadboard, resistors (10 k/220/1 k),
active buzzer.

> Parts present in the kit but currently unused in projects 01–11: NTC
> thermistor module, SW-420 vibration module — both fit nicely into the
> lesson **Challenges** (e.g., add a temperature readout or shock
> detection to the capstone).

**Important:** The RC522 runs on **3.3 V** only; NeoPixel rings accept
5 V. The ULN2003 board ships paired with the 28BYJ-48 — they're used
together, never the motor alone.
