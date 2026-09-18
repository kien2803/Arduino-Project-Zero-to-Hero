# Traffic Light — Arduino

A simple **3-LED traffic light** controller built on an Arduino UNO (compatible with Nano / Nano Every). The sketch cycles a red / green / yellow LED sequence with realistic timings:

| Phase  | LED     | Duration | Meaning                        |
|--------|---------|----------|--------------------------------|
| 1      | Red     | 5 s      | Vehicles must **STOP**         |
| 2      | Green   | 4 s      | Vehicles may **GO**            |
| 3      | Yellow  | 2 s      | **Caution** / transition       |

---

## 1. Components

| Quantity | Component                                  | Notes                                  |
|---------:|--------------------------------------------|----------------------------------------|
| 1        | Arduino UNO (or Nano / Nano Every)         | Provides 5 V GPIO                      |
| 1        | Red LED (5 mm)                             | Forward voltage ≈ 2.0 V                |
| 1        | Yellow LED (5 mm)                          | Forward voltage ≈ 2.0 V                |
| 1        | Green LED (5 mm)                           | Forward voltage ≈ 2.1 V                |
| 3        | Resistor 220 Ω, 1/4 W                      | Limits current to ≈ 14 mA per LED      |
| 1        | Breadboard + jumper wires                  | Or any traffic-light module with LEDs  |

**Resistor sizing** — for Vcc = 5 V, Vled ≈ 2 V, I ≈ 14 mA:
    R = (5 V − 2 V) / 0.014 A ≈ 214 Ω  → use **220 Ω** (standard E12 value).

---

## 2. Pin Mapping

| Arduino pin | LED     | Resistor            | LED cathode    |
|-------------|---------|---------------------|----------------|
| **D13**     | Red     | 220 Ω → anode       | → GND          |
| **D12**     | Yellow  | 220 Ω → anode       | → GND          |
| **D11**     | Green   | 220 Ω → anode       | → GND          |
| **GND**     | —       | —                   | Common rail    |

All three LED cathodes share a single wire to the Arduino **GND** pin.

---

## 3. Circuit Diagram (ASCII)

```
                              +5 V (USB)
                               |
                               |
   ARDUINO UNO                 |
  ┌────────────────┐           |
  │                │           |
  │             D13├───[220Ω]──►|──┐
  │                │           │   │
  │             D12├───[220Ω]──►|──┤
  │                │           │   │
  │             D11├───[220Ω]──►|──┤
  │                │           │   │
  │             GND├───────────┴───┴──── GND rail
  └────────────────┘
                               │
                       (common cathode)

  Legend
  ─────
  [220Ω]   current-limiting resistor
  ─►|─     LED (anode  ─►  cathode)
  Dxx      Arduino digital GPIO pin
```

A side-view ASCII schematic (closer to a schematic symbol layout):

```
           +5 V
            │
            │
   ┌────────┴────────┐
   │   RED    YEL    GRN
   │  (R)    (Y)    (G)        ← 5 mm LEDs
   └────┬─────┬─────┬──┐
        │     │     │  │
       D13   D12   D11 │
        │     │     │  │
       220Ω  220Ω  220Ω
        │     │     │  │
        └─────┴─────┴──┴─── GND  (Arduino GND pin)
```

---

## 4. How the Code Works

### `setup()`
Configures pins **D13, D12, D11** as `OUTPUT` and writes them `LOW` so every LED is off when the board starts.

### `loop()` — three phases, repeated forever
1. **RED on, others off** — `delay(5000)` waits 5 s.
2. **GREEN on, others off** — `delay(4000)` waits 4 s.
3. **YELLOW on, others off** — `delay(2000)` waits 2 s.

`digitalWrite(pin, HIGH)` sources ~5 V on the pin → current flows through the resistor → LED lights up.
`digitalWrite(pin, LOW)` pulls the pin to 0 V → no current → LED is dark.

### Timings are stored in named constants
```
RED_MS    = 5000   // 5.0 s
GREEN_MS  = 4000   // 4.0 s
YELLOW_MS = 2000   // 2.0 s
```
Change them in one place to retune the whole cycle.

---

## 5. Upload & Run

1. Open **Arduino IDE** (1.8.x or 2.x).
2. File → Open → `traffic-light.ino`.
3. Select board: **Arduino UNO** (Tools → Board).
4. Select the correct **Port** (Tools → Port).
5. Click **Upload** (→).
6. The three LEDs will start cycling automatically.

---

## 6. Extending the Project

- Replace `delay()` with `millis()`-based timing to make the cycle non-blocking (lets the Arduino do other work).
- Add a pedestrian button on D2 with an interrupt (green → blinking green → red + buzzer).
- Add a second traffic light on D8 / D7 / D6 to coordinate two intersections.
- Add a 7-segment countdown display on D2–D9 (shift register 74HC595 to save pins).
- Use PWM on a fourth yellow pin to fade between green and yellow for a smoother transition.

---

## 7. Safety Notes

- Always use a resistor with each LED — direct connection to 5 V will burn the LED.
- Do not exceed 20 mA per GPIO pin (ATmega328P absolute max ≈ 40 mA).
- Total source/sink current on all I/O pins combined ≤ 200 mA.