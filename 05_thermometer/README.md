# 05 — Room Thermometer

An NTC thermistor + math → a Celsius readout — the sensor core of every
digital thermometer and thermostat.

## Real-world problem

Digital room thermometers read a temperature-dependent resistor through
a voltage divider and convert it to degrees. This project does exactly
that — plus the validation that real instruments do when the sensor is
unplugged or shorted.

## Learning objectives

- Understand the NTC voltage divider and its orientation
- Convert ADC → voltage → resistance → temperature (Beta equation)
- Guard the math against the ADC's edge values (0 and 1023)
- Average samples to reduce measurement noise

## Prerequisites

Project 02 (`analogRead`, voltage dividers). Basic float math.

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | NTC temperature module | 10 kΩ NTC + fixed divider resistor on-board |

## Wiring

```
NTC Module       Arduino
----------       -------
VCC          --> 5V
GND          --> GND
A0 / OUT     --> A0
```

The module already contains the divider:

```
5V ---[ NTC ]---+---[ 10k fixed ]--- GND
                |
                A0
```

> With this orientation V(A0) **rises** as temperature rises. Some modules
> place the NTC toward GND — their readings move backwards (see
> Troubleshooting).

## How it works

1. The NTC's resistance falls as temperature rises → AO voltage changes.
2. `analogRead` → 0–1023 → back to voltage, then to NTC resistance:
   `R_ntc = SERIES_R × (5.0 / V − 1)`
3. The **Beta equation** (simplified Steinhart–Hart) converts resistance
   to Kelvin: `1/T = 1/T₀ + (1/β)·ln(R/R₀)` with β = 3950, T₀ = 25 °C,
   R₀ = 10 kΩ.
4. The sketch **guards the math**: `adc = 0` (A0 shorted to GND) would
   divide by zero; `adc = 1023` (open divider) would take `log` of a
   non-positive number — both print an error instead of garbage.

## The algorithm

```
every second:
    adc = average of 8 × analogRead(A0)
    if adc == 0      → error "A0 at GND — short / no sensor"
    if adc == 1023   → error "A0 at VCC — open circuit"
    voltage    = adc × (5.0 / 1023)
    resistance = SERIES_R × (5.0 / voltage − 1)
    T(C) = 1 / (ln(R/R₀)/β + 1/T₀) − 273.15
    print T, or "implausible" if outside −40..125 °C
```

## Upload & test

1. Upload `thermometer.ino`, open Serial Monitor at 9600.
2. Readings update once per second in °C.
3. Pinch the sensor — temperature climbs a few degrees.
4. Unplug A0 (open) → you should see the `ADC=1023` error, not NaN.
5. Jumper A0 to GND → `ADC=0` error. Reconnect → readings resume.

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| `ADC=0` error | A0 shorted to GND or sensor unplugged |
| `ADC=1023` error | Open divider — A0 wire off, or VCC missing |
| Temperature goes *down* when you warm the sensor | Module's NTC is on the GND side — invert the divider formula or flip the module interpretation |
| ±1 °C jumps between reads | Noise — increase `SAMPLES` |
| Values off by ~5 °C | Wrong `BETA`/`SERIES_R` for your module — check its datasheet |

## Challenges

- **Beginner:** print raw `adc` next to °C and find your room's baseline.
- **Intermediate:** show temperature on the LCD 1602 (borrow the LCD wiring from project 11).
- **Advanced:** build a two-threshold thermostat: relay/fan on at `T > 26 °C`, off at `T < 24 °C` (hysteresis).

## Knowledge check

1. Why does the divider orientation matter for the `R_ntc` formula?
2. What breaks in the math at `adc = 0` and `adc = 1023` without guards?
3. The Beta equation needs `R/R₀` — why does that make it independent of the divider's fixed resistor at exactly 25 °C?
4. Why average 8 samples instead of trusting one read?

## Safety notes

- None beyond the usual — this is a low-voltage sensing project.
