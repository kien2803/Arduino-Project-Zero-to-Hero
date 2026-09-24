# 09 — NTC Temperature Module

Read ambient temperature using the NTC thermistor module and print it to Serial Monitor.

## Description

Most NTC modules in kits use a 10 kΩ thermistor + series resistor forming a voltage divider. This sketch calculates temperature with the Beta equation (simple and accurate enough for learning).

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Module Điện Trở Nhiệt NTC | 1 |

## Wiring

```
NTC Module          Arduino
----------          -------
VCC             --> 5V
GND             --> GND
A0 / OUT        --> A0
```

## Notes on Calibration

- The constants `BETA`, `R0`, `SERIES_R` are typical values. If readings are off by a few degrees, adjust them or compare with a real thermometer.
- For better accuracy you can use the full Steinhart-Hart equation later.

## Upload & Run

Open Serial Monitor (9600). You will see temperature in °C updating every second. Touch the sensor with your finger → temperature should rise.

## Extensions

- Display temperature on LCD1602.
- Control Relay / fan when temperature > threshold (thermostat).
- Log data or send via Serial to a computer.
