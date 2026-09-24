# 10 — IR Remote + Receiver (1838T)

Receive signals from the 20-key IR remote and print the codes. Also toggles an LED.

## Description

The MH-R38 / 1838T receiver works with the common 38 kHz IR remote included in the kit. This project uses the popular `IRremote` library to decode button presses.

## Components (from kit)

| # | Component | Qty |
|---|-----------|-----|
| 1 | Arduino UNO R3 | 1 |
| 1 | Module Thu Hồng Ngoại 1838T | 1 |
| 1 | Remote Hồng Ngoại 20 Phím | 1 |
| 1 | LED (or pin 13) | 1 |

## Wiring

```
IR Receiver 1838T     Arduino
-----------------     -------
Signal (OUT)      --> D11
VCC               --> 5V
GND               --> GND
```

## Library Installation

In Arduino IDE: **Sketch → Include Library → Manage Libraries** → search **IRremote** → Install the one by **shirriff** or **ArminJo** (latest version recommended).

## Upload & Run

1. Upload the sketch.
2. Open Serial Monitor (9600).
3. Point the remote at the receiver and press buttons. You will see HEX codes.
4. LED on pin 13 toggles with every press.

## Next step

Write down the HEX code of each button you care about, then use `if (IrReceiver.decodedIRData.decodedRawData == 0xXXXX)` to control Servo, Relay, etc.
