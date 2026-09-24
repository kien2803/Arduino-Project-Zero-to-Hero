# 07 — Light Sensor

Read ambient light level and control an LED accordingly (automatic night light).

## Description

A photoresistor / LDR module outputs an analog voltage proportional to light intensity. This sketch maps the reading to LED brightness so the LED becomes brighter when the surroundings are darker.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| Light sensor module (analog output) | 1 |
| LED + 220 Ω resistor | 1 |
| Jumper wires |  |

## Wiring

```
Light Sensor Module     Arduino
-------------------     -------
VCC                 --> 5V
GND                 --> GND
A0 / OUT            --> A0

LED anode --> 220 Ω --> D9
LED cathode ---------> GND
```

## How It Works

- `analogRead(A0)` returns a value between 0 and 1023.
- `map(..., 255, 0)` inverts the value so lower light produces higher PWM duty cycle.

## Upload & Run

Open Serial Monitor at 9600 baud. Cover the sensor → LED brightens. Shine a light on it → LED dims.

## Extensions

- Add a threshold to trigger a relay or buzzer.
- Display the light level on the LCD.
