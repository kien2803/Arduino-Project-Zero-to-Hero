# 09 — Servo Barrier Gate

A miniature parking barrier / gate that opens when you press a button and closes automatically.

## What it does

- Barrier starts in the closed position (0°).
- Press the button → barrier rises to 90° (open).
- After a few seconds it returns to the closed position.

This is a simplified version of the barriers you see in parking lots and railway crossings.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| Micro Servo SG90 | 1 |
| Push button | 1 |
| Jumper wires |  |

## Wiring

```
Servo          Arduino
-----          -------
Signal     --> D9
VCC        --> 5V
GND        --> GND

Button between D2 and GND (uses internal pull-up)
```

## Upload & Test

Upload the sketch and press the button. The servo arm should rise and then lower again after 4 seconds.

## Extensions

- Open the barrier with RFID instead of a button (see next projects).
- Add an LED that is green when open and red when closed.
- Use two buttons: one for open, one for close.
