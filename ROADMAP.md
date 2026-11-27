# Curriculum Roadmap

**Arduino Project: Zero to Hero** is a 3-phase curriculum that starts with
blinking LEDs and ends with autonomous robots.

- **Phase 1 — Arduino Fundamentals** (projects 01–11, *complete*): GPIO,
  analog sensing, timing, state machines, SPI peripherals, system
  integration.
- **Phase 2 — Robotics Fundamentals** (projects 12–17, *design*): DC
  motors, drivers, distance sensing, line tracking, encoders, and a
  complete 2-wheel robot platform.
- **Phase 3 — Intelligent Robotics** (projects 18–22, *design*): PID
  control, line following, obstacle avoidance, sensor fusion, autonomous
  navigation.

> Phase 2/3 below are **curriculum designs** — prerequisites, outcomes,
> parts, and completion criteria. Implementations are planned, not yet
> written; don't expect `12_…` folders until the phase is built out.

---

## Phase 1 — Arduino Fundamentals ✅

| # | Project | Core concept |
|---|---------|--------------|
| 01–04 | Traffic light, dimmer, piano, night light | Digital/analog I/O, PWM, thresholds |
| 05–08 | Dice, LED meter, NeoPixel lamp, countdown timer | 7-segment displays, shift register, IR decode, multiplexing |
| 09–11 | Stepper, RFID access, smart door lock | Coil sequencing, SPI, state machines, integration |

Exit criteria: student can read a sensor, act on it with non-blocking
timing, and combine 3+ peripherals without pin conflicts.

---

## Phase 2 — Robotics Fundamentals (design)

### 12 — DC Motor Control
- **Prereq:** 01 (digital out), 02 (PWM)
- **Outcome:** spin a small DC motor with a transistor driver; control
  speed with a pot; understand why a GPIO can't drive a motor.
- **Parts:** 5 V DC motor + PN2222/2N2222 or L9110 module, 1N4007
  flyback diode, pot, separate power.
- **Concepts:** inductive load, flyback protection, PWM duty→speed.
- **Done when:** pot sweeps motor 0→full speed smoothly, and the board
  doesn't reset under load.

### 13 — Motor Driver Control (H-Bridge)
- **Prereq:** 12
- **Outcome:** forward/reverse/brake on command — the first real
  bidirectional control.
- **Parts:** L298N or TB6612 driver module, DC motor.
- **Concepts:** H-bridge, IN1/IN2 truth table, why you never tie them
  high together.
- **Done when:** a button toggles forward/reverse cleanly with a
  dead-time gap (no shoot-through).

### 14 — Ultrasonic Obstacle Detection
- **Prereq:** 04 (threshold logic)
- **Outcome:** measure distance with HC-SR04 and warn at a threshold —
  parking-sensor behavior.
- **Parts:** HC-SR04, buzzer.
- **Concepts:** `pulseIn`, timeout guarding, cm conversion, sensor
  dead-zones.
- **Done when:** distance prints over Serial and a buzzer alerts under
  a set range, with no hang when the echo never returns.

### 15 — IR Line Tracking Robot
- **Prereq:** 13, 14
- **Outcome:** a 2-wheel chassis follows a black line on white.
- **Parts:** 2× TCRT5000 IR line sensors + the robot chassis from 13.
- **Concepts:** differential drive, left/right correction, sensor
  hysteresis.
- **Done when:** the robot completes a taped oval without leaving the
  line at a set speed.

### 16 — Encoder & Speed Measurement
- **Prereq:** 06 (edge detection)
- **Outcome:** read wheel encoders, compute RPM, display speed.
- **Parts:** chassis + 2× slot/disc encoders (or hall + magnet).
- **Concepts:** interrupts or fast polling, ticks→RPM math, sampling
  windows.
- **Done when:** RPM readout tracks a hand-spun wheel and reads zero
  when it stops.

### 17 — Two-Wheel Mobile Robot
- **Prereq:** 13–16
- **Outcome:** the full platform — drive forward/back/turn via commands
  (Serial or IR remote from 07).
- **Parts:** 2WD chassis + driver + battery pack + (optional) IR remote.
- **Concepts:** command parsing, differential drive kinematics, power
  budgeting (motors on their own supply, common ground).
- **Done when:** the robot executes "forward 1 s → turn → forward" on
  command, repeatably.

---

## Phase 3 — Intelligent Robotics (design)

### 18 — PID Motor Speed Control
- **Prereq:** 16 (encoder RPM)
- **Outcome:** hold a target RPM despite load changes — the first
  closed-loop controller.
- **Concepts:** error, P/I/D terms, `millis()` control loop, tuning
  intuition.
- **Done when:** RPM returns to setpoint within ~1 s after a finger
  slows the wheel.

### 19 — PID Line Following
- **Prereq:** 15, 18
- **Outcome:** smooth, fast line following — not the bang-bang zigzag
  of 15.
- **Concepts:** proportional steering from a sensor *array*, PID on
  steering error.
- **Done when:** the robot follows a curved track visibly smoother and
  faster than project 15.

### 20 — Robot Obstacle Avoidance
- **Prereq:** 14, 17
- **Outcome:** autonomous roaming — the robot turns away from obstacles
  on its own.
- **Parts:** robot + HC-SR04 on a servo pan (reuse the SG90 from 09).
- **Concepts:** behavior arbitration, sensor→action mapping, escape
  states.
- **Done when:** the robot navigates a cluttered desk for 30 s without
  a collision or getting stuck.

### 21 — Sensor Fusion
- **Prereq:** 14, 16, 18
- **Outcome:** combine encoder odometry + ultrasonic + IMU for a more
  reliable position/orientation estimate than any single sensor.
- **Parts:** robot + MPU6050 (I²C) + existing sensors.
- **Concepts:** complementary filter, why sensors disagree, weighting.
- **Done when:** heading estimate stays stable through wheel slip that
  would fool encoders alone.

### 22 — Autonomous Robot Challenge
- **Prereq:** all of Phase 3
- **Outcome:** capstone — navigate a course with a line section, an
  obstacle section, and a target zone, fully autonomously.
- **Concepts:** mode-switching state machine (line-follow ↔ avoid ↔
  goal-seek), failsafes.
- **Done when:** the robot completes the full course start-to-finish
  with no human input.

---

## Adding a new phase

Each new project gets: a folder `NN_slug/` with `NN_slug.ino` (name
**must** match the folder), a README on the standard template (see
`01_traffic_light`), a row in this roadmap and the root README table,
and a compile check in CI.
