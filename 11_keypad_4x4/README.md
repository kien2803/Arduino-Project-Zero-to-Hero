# 11 — Keypad 4x4

Read keys from the membrane 4×4 keypad and print them to Serial Monitor.

## Description

The 4x4 keypad is perfect for password entry, menus, or numeric input. This project uses the standard `Keypad` library.

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Keypad 4x4 SMD | 1 |
| — | Jumper wires (8) |  |

## Wiring

Most 4x4 keypads have 8 pins: 4 rows + 4 columns (left to right when looking at the connector side).

```
Keypad pins (typical order)   Arduino
---------------------------   -------
Row 1                     --> D9
Row 2                     --> D8
Row 3                     --> D7
Row 4                     --> D6
Col 1                     --> D5
Col 2                     --> D4
Col 3                     --> D3
Col 4                     --> D2
```

If keys are wrong, swap the row/col arrays in code.

## Library

Install **Keypad** by Mark Stanley / Alexander Brevig via Library Manager.

## Upload & Run

Open Serial Monitor and press keys. You should see the corresponding character.

## Extensions

- Build a simple password lock (combine with Servo + LCD later).
- Create a calculator or menu system.
