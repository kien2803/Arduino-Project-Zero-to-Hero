# 07 — Remote Controlled Lamp

Turn a lamp (or any device) on and off with a regular TV-style IR remote.

## What it does

Press any button on the remote → the relay toggles.  
This is the same principle used in IR remote power sockets and remote-controlled lights.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| IR receiver module | 1 |
| IR remote control | 1 |
| 5 V relay module | 1 |

## Wiring

```
IR Receiver       Arduino
-----------       -------
OUT           --> D11
VCC           --> 5V
GND           --> GND

Relay Module
VCC --> 5V
GND --> GND
IN  --> D7

Connect your lamp (or a small DC load) to the relay COM + NO terminals.
```

**Safety:** If you switch mains voltage, use a proper enclosure and never touch live wires.

## Library

Install **IRremote** via the Library Manager.

## Upload & Test

1. Upload the sketch.
2. Open Serial Monitor.
3. Press any button on the remote. The relay should click and the message “Lamp ON / OFF” appears.

## Extensions

- Map specific buttons to different actions (brightness, timer, etc.).
- Add an LED that shows the current state of the lamp.
- Combine with the light sensor so the lamp only works at night.
