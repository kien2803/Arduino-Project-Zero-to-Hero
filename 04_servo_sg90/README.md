# 04 — Servo SG90

Control a micro servo motor (SG90) to sweep continuously from 0° to 180° and back.

## Description

The SG90 is a common 9 g micro servo. This project uses the built-in Servo library to generate the required PWM signal and move the servo horn smoothly between the two extremes.

## Components

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno | 1 | |
| Micro Servo SG90 | 1 | Orange = Signal, Red = VCC, Brown/Black = GND |
| Jumper wires | 3 | |

> Power note: A single SG90 can be powered from the Arduino 5 V pin. For multiple servos use an external 5 V supply and common ground.

## Wiring

```
Servo SG90          Arduino Uno
-----------         -----------
Signal (Orange) --> D9
VCC (Red)       --> 5V
GND (Brown)     --> GND
```

## How It Works

- `Servo myServo;` creates a Servo object.
- `myServo.attach(9);` assigns the control pin.
- `myServo.write(angle);` sets the target position (0–180).

The library produces a ≈50 Hz PWM signal. Pulse width determines the angle:
- ≈1.0 ms → 0°
- ≈1.5 ms → 90°
- ≈2.0 ms → 180°

## Upload & Run

1. Open `servo-sg90.ino`.
2. Select board **Arduino Uno** and the correct port.
3. Upload.
4. The servo will start sweeping automatically. Open Serial Monitor (9600 baud) to see the ready message.

## Extensions

- Control the angle with a potentiometer on A0.
- Move to fixed positions (0 / 90 / 180) with push buttons.
- Use later as the actuator in an RFID door-lock system.
