# 14 — Relay Module (1 Channel)

Control a 5 V relay to switch an external load on and off.

## Description

A relay provides electrical isolation between the Arduino and a higher-power or higher-voltage circuit. You can switch lamps, fans, solenoids, etc.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| 5 V relay module (1 channel) | 1 |

## Wiring

```
Relay Module        Arduino
------------        -------
VCC             --> 5V
GND             --> GND
IN              --> D7

Load side:
  Connect the device between COM and NO (normally open)
  or COM and NC (normally closed).
```

**Safety warning:** When switching mains voltage (110/220 V), use proper insulation, an enclosure, and never touch live terminals.

## Active High vs Active Low

Some modules energize the relay when the IN pin is LOW, others when it is HIGH. If the behavior is inverted, simply swap HIGH and LOW in the code.

## Extensions

- Control the relay from a light sensor, temperature sensor, RFID reader, or IR remote.
