# Components List

This learning path is designed around a typical Arduino Uno R3 starter kit that includes the following parts.  
You do not need every item for every project — each project README lists only the components it actually uses.

## Core Board & Power

| Item | Quantity | Notes |
|------|----------|-------|
| Arduino Uno R3 (or compatible) | 1 | Main microcontroller board |
| USB cable (Type-B) | 1 | For programming and power |
| 9V battery + battery clip to DC jack | 1 | Optional external power |
| Breadboard | 1 | For prototyping |
| Jumper wires (M-M, M-F) | 1 set | |

## Passive Components

| Item | Quantity | Notes |
|------|----------|-------|
| LED 5 mm (Red / Green / Yellow) | 10+ each | |
| Resistor 220 Ω | 10+ | Current limiting for LEDs |
| Resistor 1 kΩ | 10 | |
| Resistor 10 kΩ | 10 | |
| Potentiometer 10 kΩ (B10K) | 1 | Analog input / LCD contrast |
| Tactile push buttons | 4+ | |
| Button caps (optional) | 4 | |

## Displays

| Item | Quantity | Notes |
|------|----------|-------|
| LCD 1602 (16×2 character) | 1 | Parallel interface |
| 7-segment display 0.56" (1-digit, common anode) | 1 | |
| 7-segment display module (4-digit) | 1 | Optional |
| 8×8 LED Matrix (bi-color) | 1 | Optional |
| NeoPixel / WS2812 12-LED ring or stick | 1 | Addressable RGB |
| 74HC595 shift register | 1 | Optional, for expanding I/O |

## Motors & Actuators

| Item | Quantity | Notes |
|------|----------|-------|
| Micro Servo SG90 | 1 | 180° position control |
| Stepper motor 28BYJ-48 5 V | 1 | With reduction gearbox |
| ULN2003 stepper driver board | 1 | Required for 28BYJ-48 |
| Relay module 5 V (1-channel) | 1 | For switching higher loads |
| Active buzzer / piezo buzzer | 1 | Sound output |

## Sensors

| Item | Quantity | Notes |
|------|----------|-------|
| Light sensor module (photoresistor / LDR) | 1 | Analog output |
| Vibration / shock sensor (SW-420 style) | 1 | Digital output |
| NTC thermistor temperature module | 1 | Analog output |

## Input & Identification

| Item | Quantity | Notes |
|------|----------|-------|
| RFID RC522 module (13.56 MHz) | 1 | SPI interface, **use 3.3 V only** |
| RFID cards / key fobs | 2+ | |
| 4×4 membrane keypad | 1 | |
| IR receiver module (1838 / TSOP style) | 1 | 38 kHz |
| IR remote control | 1 | |

## Recommended Extra Tools

- Multimeter
- External 5 V power supply (for multiple motors or many NeoPixels)
- Small screwdriver (for terminal blocks if any)

---

**Tip:** Always double-check the pinout of modules (especially RFID and sensors) before connecting power. Some modules are 3.3 V only.
