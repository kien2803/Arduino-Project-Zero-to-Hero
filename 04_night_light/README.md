# 04 — Automatic Night Light

A simple corridor / bedroom night light that turns on automatically when it gets dark.

## What it does

When the ambient light falls below a threshold, the LED turns on.  
When the room becomes bright again, the LED turns off.

This is exactly how many cheap plug-in night lights work.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| Light sensor module (LDR) | 1 |
| LED + 220 Ω resistor | 1 |
| Jumper wires |  |

## Wiring

```
Light Sensor     Arduino
------------     -------
VCC          --> 5V
GND          --> GND
A0 / OUT     --> A0

LED anode --> 220 Ω --> D9
LED cathode ----------> GND
```

## How it works

1. The light sensor outputs a higher voltage in bright light and a lower voltage in the dark.
2. `analogRead(A0)` gives a number between 0 and 1023.
3. If the value is below the threshold → we consider it “dark” and turn the LED on.

You can change the `threshold` value to make the light more or less sensitive.

## Upload & Test

1. Upload the sketch.
2. Open Serial Monitor (9600 baud) to see the live light level.
3. Cover the sensor with your hand → LED should turn on.
4. Shine a phone flashlight on it → LED should turn off.

## Extensions

- Use `analogWrite()` so the LED brightness changes gradually.
- Add a second LED or a relay to control a real 12 V / 220 V lamp.
- Combine with the thermometer project to make a “night light that also shows temperature”.
