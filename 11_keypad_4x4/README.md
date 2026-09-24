# 11 — 4×4 Keypad

Read keys from a membrane 4×4 keypad and print them to the Serial Monitor.

## Description

A 4×4 keypad is ideal for password entry, menus, or numeric input. This project uses the standard Keypad library.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| 4×4 membrane keypad | 1 |
| Jumper wires (8) |  |

## Wiring

Most keypads have 8 pins: 4 rows + 4 columns.

```
Keypad (typical order)   Arduino
----------------------   -------
Row 1                --> D9
Row 2                --> D8
Row 3                --> D7
Row 4                --> D6
Col 1                --> D5
Col 2                --> D4
Col 3                --> D3
Col 4                --> D2
```

If the printed characters do not match the keys, swap the row or column pin arrays in the code.

## Library

Install **Keypad** by Mark Stanley / Alexander Brevig via the Library Manager.

## Upload & Run

Open Serial Monitor and press keys. The corresponding character should appear.

## Extensions

- Build a password lock (combine later with servo + LCD).
- Create a simple menu or calculator.
