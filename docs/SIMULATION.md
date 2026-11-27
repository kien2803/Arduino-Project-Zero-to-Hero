# Simulation vs. Hardware

Every project runs in a simulator for learning the logic — but a few
behaviors only appear on real hardware. Know which you're testing.

## Simulating

**Wokwi** (https://wokwi.com) runs Uno + most of these peripherals free
in the browser. Paste the `.ino`, wire the parts, run.

- Works well: LEDs, buttons, pots, servo, LCD, keypad, HC-SR04.
- Approximated: IR remote (use the built-in NEC remote), NTC/LDR
  (drag a slider instead of real physics).
- Not simulatable reliably: RC522 RFID (no model) — projects 10/11
  need real cards.

## Where simulation lies

| Thing | In sim | On hardware |
|---|---|---|
| `delay()` vs `millis()` | both "work" | only `millis()` stays responsive under load |
| Debounce | buttons are ideal | real contacts bounce — you need the code |
| ADC edge cases | sliders rarely hit 0/1023 | real dividers hit both — guards matter |
| Servo brown-out | never happens | stalled SG90 can reset the board |
| IR repeat frames | one click = one frame | held button floods repeats |
| Pin conflicts | may still "work" | two outputs on one pin corrupts silently |

## Rule of thumb

Simulate to learn the *logic*; run on hardware to learn the *engineering*.
The challenges marked **Advanced** in each lesson assume a real board.
