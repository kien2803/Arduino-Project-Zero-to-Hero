# 05 — Stepper Motor 28BYJ-48 + ULN2003

Drive the popular 5 V 28BYJ-48 stepper motor using the ULN2003 driver board.

## Description

The 28BYJ-48 is a unipolar stepper with a high gear reduction. Together with the ULN2003 driver it allows precise angular control. This sketch rotates one full revolution clockwise, then counter-clockwise.

## Components

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno | 1 | |
| Stepper motor 28BYJ-48 5 V | 1 | |
| ULN2003 driver board | 1 | |
| Jumper wires | 6 | |

## Wiring

```
ULN2003          Arduino Uno
-------          -----------
IN1          --> D8
IN2          --> D9
IN3          --> D10
IN4          --> D11
+ (5–12 V)   --> 5V   (or external 5 V for higher torque)
-            --> GND

Plug the motor connector directly into the ULN2003 socket.
```

> Note: On some driver boards the pin order may be IN1-IN3-IN2-IN4. If the motor only vibrates, swap the middle two wires in code.

## How It Works

- `stepsPerRevolution = 2048` is the typical value for the 28BYJ-48 in full-step mode.
- The Stepper library handles the stepping sequence.
- Positive steps turn one direction, negative steps the opposite direction.

## Upload & Run

Upload the sketch. The motor will rotate 360° CW → pause → 360° CCW repeatedly. Watch the Serial Monitor for direction messages.

## Extensions

- Vary speed with a potentiometer.
- Combine with a servo for a simple two-axis mechanism.
- Use for precise positioning tasks (display turntable, barrier, etc.).
