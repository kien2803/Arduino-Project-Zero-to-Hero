# 09 — NTC Temperature Sensor

Read temperature with an NTC thermistor module and print the value in Celsius.

## Description

Typical NTC modules use a 10 kΩ thermistor in a voltage divider. This sketch calculates temperature using the Beta equation, which is accurate enough for learning purposes.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| NTC thermistor module | 1 |

## Wiring

```
NTC Module          Arduino
----------          -------
VCC             --> 5V
GND             --> GND
A0 / OUT        --> A0
```

## Notes on Accuracy

The constants `BETA`, `R0` and `SERIES_R` are typical values. If the reading is a few degrees off, compare with a reference thermometer and adjust the constants.

## Upload & Run

Open Serial Monitor (9600 baud). Temperature updates every second. Touch the sensor with your finger and watch the value rise.

## Extensions

- Show the temperature on the LCD.
- Control a relay or fan when temperature exceeds a threshold (simple thermostat).
