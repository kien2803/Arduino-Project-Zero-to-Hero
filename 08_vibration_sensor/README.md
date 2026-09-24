# 08 — Vibration Sensor

Detect shock or vibration and trigger an LED plus a short beep.

## Description

Digital vibration/shock modules (SW-420 style) change their output state when movement exceeds an adjustable threshold. This project lights an LED and activates a buzzer on detection.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| Vibration sensor module | 1 |
| Active / piezo buzzer | 1 |
| LED (or use pin 13) | 1 |

## Wiring

```
Vibration Module     Arduino
----------------     -------
VCC              --> 5V
GND              --> GND
DO               --> D2

Buzzer +         --> D8
Buzzer -         --> GND
```

Most modules have a small potentiometer for sensitivity adjustment. Turn it until the onboard LED stays off when the board is still.

## Upload & Run

Upload, then gently tap or shake the sensor. The LED should light and a short beep should sound. Serial Monitor prints “Vibration detected!”.

## Extensions

- Count the number of vibrations.
- Use as a simple anti-theft alarm (arm/disarm with RFID later).
- Trigger a relay.
