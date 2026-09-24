# 04 — Automatic Night Light

A simple automatic night light using a **4-pin light sensor module**.

## What it does

When the surrounding light becomes low, the LED turns on.  
When it becomes bright again, the LED turns off.

This is the same idea used in many inexpensive plug-in night lights.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| 4-pin Light Sensor module (MS-CDS05 style) | 1 |
| LED | 1 |
| 220 Ω resistor | 1 |
| Jumper wires |  |

## 4-pin Light Sensor Pinout

| Pin on module | Connect to Arduino |
|---------------|--------------------|
| VCC           | 5V                 |
| GND           | GND                |
| AO            | A0                 |
| DO            | D2                 |

The module has a small blue potentiometer.  
Turning it changes the switching point of the **DO** pin.

## Wiring

```
Light Sensor (4-pin)      Arduino
--------------------      -------
VCC                   --> 5V
GND                   --> GND
AO                    --> A0
DO                    --> D2

LED anode  --> 220 Ω --> D9
LED cathode ----------> GND
```

## How it works

1. The sensor measures ambient light.
2. **AO** gives a continuous analog value (0–1023).
3. **DO** gives a simple digital signal (HIGH or LOW) according to the potentiometer setting.
4. In this project we use the **DO** pin because it is the easiest way.

Most modules of this type output **LOW on DO when it is dark**.  
If your LED turns on in bright light instead of dark light, just change `LOW` to `HIGH` in the code.

## Upload & Test

1. Upload the sketch.
2. Open Serial Monitor (9600 baud). You will see AO and DO values updating.
3. Cover the sensor with your hand → LED should turn on.
4. Remove your hand or shine a light → LED should turn off.
5. Adjust the blue potentiometer on the module until the switching point feels right for your room.

## Tips

- Watch the Serial Monitor while turning the potentiometer. This makes adjustment very easy.
- If the analog values are inverted on your module (high number = bright), that is normal. We mainly use the DO pin in this project.

## Extensions

- Use the AO value with `analogWrite()` to make the LED brightness change gradually.
- Add a relay to control a real 12 V or 220 V lamp.
- Combine later with the thermometer project.
