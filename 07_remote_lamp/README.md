# 07 — Remote Controlled Lamp

Turn a lamp on and off with one specific button on a regular IR remote —
the way IR remote sockets and remote-controlled lights work.

## Real-world problem

Remote power sockets decode an IR command from a handset and toggle a
relay — but only for *their* button, and only *once* per press. This
project decodes NEC-style IR frames, filters out the auto-repeat frames
a remote sends while a button is held, and toggles only on the command
you choose.

## Learning objectives

- Receive and decode IR signals with the **IRremote** library
- Tell real presses from **repeat frames** (`IRDATA_FLAGS_IS_REPEAT`)
- Map a specific remote command to an action (not "any button")
- Drive a 5 V relay module for a load that a GPIO pin can't power

## Prerequisites

Projects 01 (digital output), 03 (Serial Monitor basics).

## Components

| Qty | Component | Notes |
|----:|-----------|-------|
| 1 | Arduino Uno | |
| 1 | IR receiver module | VS1838B / TSOP1738 style, 38 kHz |
| 1 | IR remote control | Any NEC-protocol TV/DVD remote |
| 1 | 5 V relay module (1 ch) | Opto-isolated preferred |

## Wiring

```
IR Receiver       Arduino
-----------       -------
OUT           --> D11
VCC           --> 5V
GND           --> GND

Relay Module
VCC --> 5V     GND --> GND     IN --> D7
```

| Signal | Arduino pin |
|--------|-------------|
| IR receiver OUT | **D11** |
| Relay IN | **D7** |

Connect the lamp/load to the relay's **COM + NO** terminals — the relay
switches the load's *own* power, not the Arduino's.

## Library

Install **IRremote** (≥ 4.x — this sketch uses the v4 API:
`IrReceiver`, `decodedIRData`, `IRDATA_FLAGS_IS_REPEAT`).

## How it works

1. The receiver decodes bursts of 38 kHz IR into protocol + address +
   command.
2. Most NEC-style remotes resend a short **repeat frame** while the
   button is held — without filtering, one press toggles the relay
   several times a second.
3. The sketch drops repeat frames, prints `protocol=`/`command=` for
   every *real* frame, and toggles only when `command == CMD_POWER`.
4. First-run setup: press your remote's buttons, read their command
   codes on Serial, put the one you want into `CMD_POWER`, re-upload.

## The algorithm

```
loop forever:
    if a frame was decoded:
        if it's a REPEAT frame → discard (held button)
        print protocol + command
        if command == CMD_POWER → toggle lampState, drive relay
```

## Upload & test

1. Upload `07_remote_lamp.ino`, open Serial Monitor.
2. Press remote buttons — each real press prints its command code.
3. Copy your chosen button's code into `CMD_POWER`, re-upload.
4. Press that button → relay clicks ON; press again → OFF.
   **Hold** it → exactly one toggle (repeat frames are filtered).

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Nothing decoded | Receiver OUT not on D11, or remote isn't NEC — check Serial for `protocol=` output |
| Lamp toggles 2–3× per press | Repeat frames — check your IRremote version is ≥ 4.x and the `IS_REPEAT` check is present |
| Wrong button toggles | Command code differs — read it on Serial and update `CMD_POWER` |
| Relay clicks but lamp doesn't | Load wired to NC instead of NO — use **COM + NO** |
| LED on receiver module doesn't blink | Receiver not powered — check VCC/GND |

## Challenges

- **Beginner:** map a second command (e.g. `CMD_TIMER`) to blink the lamp on/off as a "standby" indicator.
- **Intermediate:** add an LED that shows current lamp state (it's the relay's job to switch the real load).
- **Advanced:** only allow the lamp when the room is dark — combine with project 04's light sensor AND the IR command.

## Knowledge check

1. Why does holding a remote button send repeat frames, and why must they be filtered here?
2. The sketch prints `command=` for every button — why is that step needed before hardcoding `CMD_POWER`?
3. Why is the lamp driven by a relay instead of a GPIO pin directly?
4. What does `IrReceiver.resume()` do, and what happens if you forget it?

## Safety notes

- **Do not switch mains voltage in this course.** Use a 5 V lamp, LED
  strip, or small DC load through the relay. If you ever do use mains,
  it needs a proper enclosure and someone qualified — never a breadboard.
- Relay module VCC goes to 5 V — not to the relay's load terminals.
