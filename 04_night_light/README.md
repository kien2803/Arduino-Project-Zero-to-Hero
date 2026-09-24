# 04 — Automatic Night Light (4-pin RGB LED)

A soft night light that turns on automatically when the room becomes dark.  
Uses a **4-pin RGB LED** so you can choose any color.

## What it does

When the ambient light falls below a threshold, the RGB LED lights up with a warm color.  
When the room becomes bright again, the LED turns off.

This is how many modern night lights and smart bulbs behave — only simplified.

## Components

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno | 1 | |
| Light sensor module (LDR) | 1 | Analog output |
| **4-pin RGB LED** | 1 | R, G, B + Common |
| Resistors 220 Ω | 3 | One for each color pin |
| Jumper wires |  | |

## Understanding the 4-pin RGB LED

A 4-pin RGB LED has:

- 3 color pins: **Red**, **Green**, **Blue**
- 1 common pin (longest pin or marked pin)

There are two types:

| Type | Common pin connects to | How to turn a color ON |
|------|------------------------|------------------------|
| **Common Cathode** | GND | Send HIGH / PWM to the color pin |
| **Common Anode** | 5V | Send LOW / inverted PWM to the color pin |

Most cheap kit RGB LEDs are **Common Cathode**.  
If the colors are inverted (LED stays on when it should be off), change this line in the code:

```cpp
const bool COMMON_ANODE = true;   // or false
```

## Wiring

```
Light Sensor          Arduino
------------          -------
VCC               --> 5V
GND               --> GND
A0 / OUT          --> A0

4-pin RGB LED
-------------
Red pin    --> 220 Ω --> D9
Green pin  --> 220 Ω --> D10
Blue pin   --> 220 Ω --> D11
Common     --> GND   (if Common Cathode)
           --> 5V    (if Common Anode)
```

## How it works

1. The light sensor gives a higher value in bright light and a lower value in the dark.
2. When the value drops below `threshold`, we call `setColor()` with a warm orange.
3. `analogWrite()` on the three pins creates any color by mixing Red, Green and Blue.

You can easily change the night-light color by editing the numbers inside `setColor(r, g, b)`.

## Upload & Test

1. Upload the sketch.
2. Open Serial Monitor (9600 baud) to see the live light level.
3. Cover the sensor with your hand → RGB LED should glow warm orange.
4. Shine a light on the sensor → LED turns off.

If the LED behaves opposite (on when bright), set `COMMON_ANODE = true` and upload again.

## Extensions

- Make the brightness change smoothly with the light level (`map()` + `analogWrite`).
- Different colors for different light ranges (blue at dusk, warm at night, etc.).
- Add a button to cycle through favorite night-light colors.
- Combine with the thermometer project later.
