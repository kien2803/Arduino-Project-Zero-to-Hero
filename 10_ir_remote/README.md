# 10 — IR Remote Control

Receive signals from a common 38 kHz IR remote and print the button codes. Also toggles an LED.

## Description

IR receiver modules (1838 / TSOP style) work with most inexpensive remote controls. This project uses the IRremote library to decode button presses.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| IR receiver module | 1 |
| IR remote control | 1 |
| LED (or pin 13) | 1 |

## Wiring

```
IR Receiver         Arduino
-----------         -------
Signal (OUT)    --> D11
VCC             --> 5V
GND             --> GND
```

## Library Installation

In Arduino IDE go to **Sketch → Include Library → Manage Libraries**, search for **IRremote**, and install a recent version.

## Upload & Run

1. Upload the sketch.
2. Open Serial Monitor (9600 baud).
3. Point the remote at the receiver and press buttons. HEX codes will appear.
4. The LED on pin 13 toggles with every press.

## Next Steps

Record the HEX code of each useful button, then use conditional statements to control a servo, relay, or other outputs.
