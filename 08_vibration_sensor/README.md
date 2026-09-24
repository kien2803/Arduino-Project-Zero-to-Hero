# 08 — Vibration Sensor SW-420

Detect shock or vibration and trigger an LED + buzzer alarm.

## Description

The SW-420 is a digital vibration/shock sensor. When it detects movement above its sensitivity threshold it changes the digital output state. This project turns on the onboard LED and beeps the chip buzzer.

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Module Cảm Biến Rung SW-420 | 1 |
| 1 | Còi Chip 5V | 1 |
| 1 | LED (or use pin 13) | 1 |

## Wiring

```
SW-420 Module       Arduino
-------------       -------
VCC             --> 5V
GND             --> GND
DO              --> D2

Buzzer +        --> D8
Buzzer -        --> GND
```

Most SW-420 modules have a potentiometer to adjust sensitivity. Turn it until the LED on the module just stays off when the board is still.

## Upload & Run

Upload, then gently tap or shake the sensor. You should see the LED light up and hear a short beep. Serial Monitor will print “Vibration detected!”.

## Extensions

- Count number of vibrations.
- Use as anti-theft alarm with RFID arm/disarm.
- Trigger Relay to cut power or send signal.
