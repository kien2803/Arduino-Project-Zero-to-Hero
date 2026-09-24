# 04 — Servo SG90

Control a micro servo motor (SG90) to sweep from 0° to 180° and back.

## Description

The SG90 is a popular 9g micro servo. This project uses the built-in `Servo` library to continuously sweep the horn between 0 and 180 degrees. Perfect introduction to position control and PWM signal generation for motors.

## Components (from your BanLinhKien kit)

| # | Component | Qty | Notes |
|---|-----------|-----|-------|
| 1 | Arduino UNO R3 | 1 | |
| 1 | Servo SG90 | 1 | Orange = Signal, Red = VCC, Brown = GND |
| — | Jumper wires | 3 | |

> **Power note**: For a single SG90 you can power from Arduino 5V. For multiple servos use external 5V supply.

## Wiring

```
Servo SG90          Arduino UNO
-----------         -----------
Signal (Orange) --> D9
VCC    (Red)    --> 5V
GND    (Brown)  --> GND
```

## Code Highlights

- `Servo myServo;` creates a Servo object.
- `myServo.attach(9);` tells the library which pin generates the PWM signal.
- `myServo.write(angle);` sets the target angle (0–180).

## How It Works

The library generates a ~50 Hz PWM signal. Pulse width determines angle:
- ~1 ms → 0°
- ~1.5 ms → 90°
- ~2 ms → 180°

## Upload & Run

1. Open `servo-sg90.ino` in Arduino IDE.
2. Select board **Arduino Uno** and correct Port.
3. Upload.
4. Servo will start sweeping automatically. Open Serial Monitor (9600) to see ready message.

## Extensions

- Control angle with potentiometer (B10K in kit) on A0.
- Use with RFID or Keypad later for door lock project.
- Add button to move to specific angles (0 / 90 / 180).
