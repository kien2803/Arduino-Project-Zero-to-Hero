# 12 — 7-Segment 1 Digit (Common Anode)

Count from 0 to 9 on the single 0.56" red 7-segment display (common anode).

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | LED 7 0.56Inch 1 Số Anode | 1 |
| 7 | Resistor 220 Ω | 7 | One per segment |

## Wiring (typical for common anode)

```
Segment   Arduino pin   via 220Ω
a     --> D2
b     --> D3
c     --> D4
d     --> D5
e     --> D6
f     --> D7
g     --> D8
Common Anode --> 5V
```

Because it is **common anode**, a segment lights when the Arduino pin is driven **LOW**.

## Note

The bit patterns in the code assume a specific segment order. If digits look wrong, rearrange the `segPins` array or the bit patterns.

## Extensions

- Use 74HC595 to drive it with only 3 Arduino pins.
- Make a simple stopwatch or dice.
