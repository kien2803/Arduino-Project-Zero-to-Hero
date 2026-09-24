# 12 — 7-Segment Display (1 Digit)

Count from 0 to 9 on a single-digit common-anode 7-segment display.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| 7-segment display 0.56" (common anode) | 1 |
| Resistor 220 Ω | 7 | One per segment |

## Wiring (common anode)

```
Segment   Arduino pin (via 220 Ω)
a     --> D2
b     --> D3
c     --> D4
d     --> D5
e     --> D6
f     --> D7
g     --> D8
Common Anode --> 5V
```

Because the display is common anode, a segment lights when the Arduino pin is driven **LOW**.

## Note

The bit patterns assume a specific segment order. If digits look incorrect, rearrange the `segPins` array or the patterns in the code.

## Extensions

- Drive the display with a 74HC595 to free up Arduino pins.
- Build a simple stopwatch or electronic die.
