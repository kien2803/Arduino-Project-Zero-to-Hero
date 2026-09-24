# 14 — Relay Mini 1 Channel 5V

Control the 5V relay module to switch a higher-power load (lamp, fan, solenoid, etc.).

## Description

The relay provides galvanic isolation. You can safely switch 220 V AC devices (with proper caution) or 12 V DC loads.

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Module Relay Mini 1 Kênh 5V10A | 1 |

## Wiring

```
Relay Module        Arduino
------------        -------
VCC             --> 5V
GND             --> GND
IN              --> D7

Load side (NO / COM / NC):
  Connect your device between COM and NO (normally open)
  or COM and NC (normally closed)
```

**Safety warning**: When switching mains voltage (220 V), use proper insulation, enclosure and never touch live terminals.

## Active High / Active Low

Some modules turn the relay ON when IN is LOW, others when HIGH. If the LED behavior is inverted, just swap HIGH/LOW in the code.

## Extensions

- Control with light sensor, temperature, RFID, or IR remote.
