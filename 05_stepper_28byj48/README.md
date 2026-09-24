# 05 — Stepper Motor 28BYJ-48 + ULN2003

Drive the 5V 28BYJ-48 stepper motor using the ULN2003 driver board included in the kit.

## Description

The 28BYJ-48 is a unipolar stepper commonly found in kits. With the ULN2003 driver it becomes easy to control precise angular movement. This project rotates one full revolution clockwise, then counter-clockwise.

## Components (from kit)

| # | Component | Qty | Notes |
|---|-----------|-----|-------|
| 1 | Arduino UNO R3 | 1 | |
| 1 | Stepper 28BYJ-48 5V | 1 | |
| 1 | Module ULN2003 | 1 | Driver board |
| — | Jumper wires | 6 | |

## Wiring

```
ULN2003          Arduino UNO
-------          -----------
IN1          --> D8
IN2          --> D9
IN3          --> D10
IN4          --> D11
+ (5–12V)    --> 5V  (or external 5V for more torque)
-            --> GND

Motor connector → plug directly into ULN2003 socket
```

> Note: Pin order on some ULN2003 boards may be IN1-IN3-IN2-IN4. Adjust if motor vibrates instead of rotating smoothly.

## Code Highlights

- `stepsPerRevolution = 2048` (typical value for 28BYJ-48 in full-step mode with gear reduction).
- `Stepper myStepper(steps, pin1, pin3, pin2, pin4);` — order matters!
- `myStepper.setSpeed(10);` sets RPM.
- Positive steps = one direction, negative = opposite.

## Upload & Run

Upload the sketch. Motor will rotate 360° CW → pause → 360° CCW repeatedly. Watch Serial Monitor for direction messages.

## Extensions

- Control speed/direction with potentiometer or buttons.
- Combine with Servo for simple robotic arm.
- Use for precise positioning (e.g. rotating display or barrier).
