# 04 — Automatic Night Light

A simple night light that turns on automatically when the surroundings become dark.  
Designed for a **4-pin light sensor module** (VCC, GND, AO, DO).

## What it does

When the light level drops, the LED turns on.  
When it becomes bright again, the LED turns off.

This is the same working principle as many cheap automatic night lights.

## Components

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno | 1 | |
| **4-pin Light Sensor module** | 1 | Pins: VCC, GND, AO, DO |
| LED + 220 Ω resistor | 1 | Or one color of an RGB LED |
| Jumper wires |  | |

## Understanding the 4-pin Light Sensor

Most 4-pin light sensor modules have:

| Pin | Name | Function |
|-----|------|----------|
| 1 | VCC | 3.3V or 5V |
| 2 | GND | Ground |
| 3 | AO | Analog Output (0–1023) |
| 4 | DO | Digital Output (HIGH/LOW) |

The module usually has a small blue potentiometer.  
Turning it changes the threshold of the **DO** pin.

- AO → gives a continuous value (more precise)
- DO → simple HIGH/LOW signal (very easy to use)

## Wiring

```
Light Sensor (4-pin)     Arduino
--------------------     -------
VCC                  --> 5V
GND                  --> GND
AO                   --> A0
DO                   --> D2

LED anode --> 220 Ω --> D9
LED cathode ----------> GND
```

## How it works

1. The sensor measures ambient light.
2. We read both AO (analog) and DO (digital).
3. In the default code we use the **DO pin**:
   - When it is dark → DO becomes LOW → LED turns ON
   - When it is bright → DO becomes HIGH → LED turns OFF

You can also switch to the analog method by uncommenting the second part of the code and adjusting the `threshold` value.

## Upload & Test

1. Upload the sketch.
2. Open Serial Monitor (9600 baud).
3. You will see both AO and DO values live.
4. Cover the sensor with your hand → LED should turn on.
5. Shine a light on it → LED should turn off.

If the LED behavior is reversed, just swap the `HIGH` / `LOW` in the `if` statement, or adjust the potentiometer on the sensor module.

## Tips

- Turn the potentiometer on the module while watching the Serial Monitor until DO changes cleanly between bright and dark.
- For smoother control, use the analog method (`analogRead`) and `analogWrite` on the LED for gradual brightness.

## Extensions

- Make the LED brightness change smoothly according to the AO value.
- Use an RGB LED and change color based on light level.
- Add a relay to control a real lamp.
