# 05 — Room Thermometer

A simple digital thermometer that shows the room temperature.

## What it does

Reads the temperature from an NTC thermistor module and prints it in Celsius every second.  
This is the core of every digital room thermometer, weather station, or thermostat.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| NTC temperature module | 1 |

## Wiring

```
NTC Module       Arduino
----------       -------
VCC          --> 5V
GND          --> GND
A0 / OUT     --> A0
```

## How it works

The NTC changes resistance with temperature.  
The module forms a voltage divider. We measure the voltage, calculate the resistance, then convert it to temperature using the Beta equation (a simplified Steinhart-Hart formula).

## Upload & Test

1. Upload the sketch.
2. Open Serial Monitor at 9600 baud.
3. You should see the temperature updating once per second.
4. Hold the sensor between your fingers → the temperature rises.

## Extensions

- Display the temperature on an LCD 1602.
- Add a relay to turn on a fan or heater when temperature crosses a limit (simple thermostat).
- Log the temperature over time.
