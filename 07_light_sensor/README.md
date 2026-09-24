# 07 — Light Sensor (MS-CDS05)

Read ambient light level with the photoresistor module and control an LED accordingly.

## Description

The MS-CDS05 module outputs an analog voltage proportional to light intensity. This project maps the reading to LED brightness (acts as an automatic night light) and also prints values to Serial Monitor.

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Module Cảm Biến Ánh Sáng MS-CDS05 | 1 |
| 1 | LED 5mm + 220Ω resistor | 1 |
| — | Jumper wires |  |

## Wiring

```
Light Sensor Module     Arduino
-------------------     -------
VCC                 --> 5V
GND                 --> GND
A0 (or OUT)         --> A0

LED anode --> 220Ω --> D9
LED cathode ---------> GND
```

> Some modules have both digital (DO) and analog (AO) pins. Use the analog pin for this sketch.

## How It Works

- `analogRead(A0)` returns 0–1023.
- `map(..., 255, 0)` inverts the value so the LED gets brighter when the environment is darker.

## Upload & Run

Open Serial Monitor at 9600 baud. Cover the sensor with your hand → LED should brighten. Shine a light → LED dims.

## Extensions

- Add threshold to trigger Relay or Buzzer.
- Combine with LCD to show “Light Level: xxx”.
