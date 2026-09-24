# Arduino Project Zero to Hero

A complete beginner-to-intermediate learning path for Arduino.  
Start with simple digital outputs and finish with a full RFID access-control system.

> **Status:** Active — 16 self-contained projects ordered by increasing complexity.

---

## Table of Contents

| # | Project | Level | Key Concepts |
|---|---------|-------|--------------|
| 01 | [Traffic Light](./01_traffic_light/) | Beginner | `digitalWrite`, `delay`, sequencing |
| 02 | [Dimmer LED](./02_dimmer_led/) | Beginner | `analogRead`, PWM, `map()` |
| 03 | [Piano](./03_piano/) | Beginner | `tone()`, `INPUT_PULLUP` |
| 04 | [Servo SG90](./04_servo_sg90/) | Beginner | Servo library, position control |
| 05 | [Stepper Motor](./05_stepper_28byj48/) | Intermediate | Stepper library, precise rotation |
| 06 | [LCD 1602](./06_lcd1602/) | Intermediate | LiquidCrystal, 4-bit mode |
| 07 | [Light Sensor](./07_light_sensor/) | Beginner | Analog sensor, threshold logic |
| 08 | [Vibration Sensor](./08_vibration_sensor/) | Beginner | Digital sensor, simple alarm |
| 09 | [NTC Temperature](./09_ntc_temperature/) | Intermediate | Thermistor, Beta equation |
| 10 | [IR Remote](./10_ir_remote/) | Intermediate | IRremote library |
| 11 | [Keypad 4×4](./11_keypad_4x4/) | Intermediate | Matrix keypad scanning |
| 12 | [7-Segment Display](./12_seven_segment_1digit/) | Intermediate | Common-anode patterns |
| 13 | [RFID RC522 Basic](./13_rfid_rc522/) | Intermediate | SPI, read UID |
| 14 | [Relay](./14_relay/) | Beginner | Switching external loads |
| 15 | [NeoPixel](./15_neopixel/) | Intermediate | Addressable RGB LEDs |
| 16 | [**RFID Door Lock**](./16_rfid_door_lock/) | Flagship | Full system integration |

See also: **[COMPONENTS.md](./COMPONENTS.md)** — complete parts list.

---

## Learning Path

```
Digital I/O          →  01, 03, 14
Analog & PWM         →  02, 07
Motors               →  04, 05
Displays             →  06, 12, 15
Sensors              →  08, 09
User Input           →  10, 11
RFID Foundation      →  13
Capstone Project     →  16  (RFID + Servo + LCD + Buzzer + LEDs)
```

After completing project 16 you will have solid practical skills ready for more advanced topics (ESP32, IoT, industrial controllers, etc.).

---

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Connect your Arduino Uno with a USB cable.
3. In the IDE select **Tools → Board → Arduino Uno** and the correct **Port**.
4. Open any project folder, open the `.ino` file, and click **Upload**.

Required third-party libraries (install via Library Manager when needed):

- MFRC522
- Keypad
- IRremote
- Adafruit NeoPixel

---

## Project Structure

Every project folder contains:

- `*.ino` — ready-to-upload sketch
- `README.md` — description, components, wiring, explanation, and extension ideas

---

## License

MIT License. Feel free to fork, modify, and share.

Happy making!
