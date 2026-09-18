# 02 — Dimmer LED (Potentiometer)

Control LED brightness with a potentiometer through an analog signal.

## Description

Read the analog value from pin `A0` (10 kΩ potentiometer wired between `5V` and `GND`), map it to the 8-bit PWM range (0–255), and output it on PWM pin `9` so the LED brightness tracks the potentiometer position.

## Components

| # | Component | Qty | Notes |
|---|-----------|-----|-------|
| 1 | Arduino Uno / Nano | 1 | Or any ATmega328P-based board |
| 1 | LED | 1 | Any color |
| 1 | Current-limiting resistor for LED | 1 | ~220 Ω |
| 1 | Potentiometer | 1 | 10 kΩ linear taper |
| — | Breadboard + jumper wires | 1 set | |

## Wiring

```
                +5V
                 |
                [POT]   ← 10 kΩ potentiometer (3 pins: VCC, GND, WIPER)
                 |
                 +----------> A0  (Arduino)
                 |
                GND

  Pin 9 (Arduino) ----[ 220 Ω ]---->|---- GND   (LED + resistor)
```

- **Potentiometer**: outer pins to `5V` and `GND`, wiper (middle pin) to `A0`.
- **LED**: anode to `D9` through the 220 Ω resistor, cathode to `GND`.

> Pin `9` on Arduino Uno is a PWM pin (`~`), compatible with `analogWrite()`.

## Code (`dimmer-led.ino`)

```cpp
int ledPin = 9;
int potPin = A0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);

  int brightness = map(potValue, 0, 1023, 0, 255);

  analogWrite(ledPin, brightness);
}
```

## How It Works

1. `analogRead(A0)` returns a **10-bit** ADC value in `0–1023`, proportional to the voltage at the wiper.
2. `map(potValue, 0, 1023, 0, 255)` linearly scales it down to the **8-bit** range matching the PWM duty-cycle.
3. `analogWrite(9, brightness)` generates a PWM signal at ~490 Hz with a proportional duty-cycle, dimming or brightening the LED.
4. `loop()` runs continuously, so the LED tracks the potentiometer in near real time.

```mermaid
flowchart LR
  POT["A0<br/>potentiometer"] -->|analogRead<br/>0–1023| MCU{{"Arduino"}}
  MCU -->|analogWrite<br/>0–255| PWM["D9 ~PWM"]
  PWM --> R["220 Ω"] --> LED["LED"] --> GND[("GND")]
```

## Uploading

1. Open Arduino IDE and install the **Arduino Uno** board (or your board's core).
2. Select the correct COM port under **Tools → Port**.
3. Open `dimmer-led.ino` and click **Upload** (Ctrl+U).
4. Turn the potentiometer to change the LED brightness.

## Possible Improvements

- **Smooth ADC readings**: average several `analogRead()` samples or use a moving average to suppress noise.
- **Higher-frequency PWM**: on ATmega328P, raise the PWM frequency via `TCCR1B` (timer 1) to avoid visible flicker with some LEDs.
- **Dead-zone near zero**: treat `brightness < 5` as fully off so a near-zero duty-cycle doesn't leave a faint flicker.
