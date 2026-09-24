# Arduino Project Zero to Hero

A curated, beginner-friendly path through classic Arduino projects — from blinking a single LED to building a complete RFID door-lock system using the **BanLinhKien Arduino Uno R3 RFID Kit**.

> **Status:** Active development — projects added in increasing complexity, fully matched to the components in the kit.

---

## Table of Contents

| # | Project | Difficulty | Core concepts / Kit parts used |
|---|---------|------------|--------------------------------|
| 01 | [Traffic Light](./01_traffic_light/) | 🟢 Beginner | `digitalWrite`, `delay`, sequencing |
| 02 | [Dimmer LED (Potentiometer)](./02_dimmer_led/) | 🟢 Beginner | `analogRead`, PWM, `map()`, B10K |
| 03 | [Piano (Buzzer + Buttons)](./03_piano/) | 🟢 Beginner | `tone()`, `INPUT_PULLUP`, Còi chip |
| 04 | [Servo SG90](./04_servo_sg90/) | 🟢 Beginner | Servo library, position control |
| 05 | [Stepper 28BYJ-48 + ULN2003](./05_stepper_28byj48/) | 🟡 Intermediate | Stepper library, precise rotation |
| 06 | [LCD 1602](./06_lcd1602/) | 🟡 Intermediate | LiquidCrystal, 4-bit mode, contrast pot |
| 07 | [Light Sensor MS-CDS05](./07_light_sensor/) | 🟢 Beginner | Analog sensor, night-light logic |
| 08 | [Vibration Sensor SW-420](./08_vibration_sensor/) | 🟢 Beginner | Digital sensor, alarm |
| 09 | [NTC Temperature](./09_ntc_temperature/) | 🟡 Intermediate | Thermistor, Beta equation |
| 10 | [IR Remote + 1838T](./10_ir_remote/) | 🟡 Intermediate | IRremote library, decode buttons |
| 11 | [Keypad 4x4](./11_keypad_4x4/) | 🟡 Intermediate | Keypad library, matrix scanning |
| 12 | [7-Segment 1 Digit](./12_seven_segment_1digit/) | 🟡 Intermediate | Common anode, segment patterns |
| 13 | [RFID RC522 Basic](./13_rfid_rc522/) | 🟡 Intermediate | MFRC522, SPI, read UID |
| 14 | [Relay 1 Channel](./14_relay/) | 🟢 Beginner | Digital output, load switching |
| 15 | [NeoPixel 12 LED](./15_neopixel/) | 🟡 Intermediate | Adafruit NeoPixel, addressable RGB |
| 16 | [**RFID Door Lock**](./16_rfid_door_lock/) | 🔴 Flagship | RFID + Servo + LCD + Buzzer + LEDs |

More projects (LED Matrix, 74HC595, 4-digit 7-segment, combined systems…) coming soon.

---

## Folder Structure

```
Arduino-Project-Zero-to-Hero/
├── README.md
├── 01_traffic_light/
├── 02_dimmer_led/
├── …
├── 16_rfid_door_lock/
│   ├── rfid-door-lock.ino
│   └── README.md
└── …
```

Each project folder is **standalone** — open its `.ino` and you are ready to upload.

---

## Recommended Learning Path (with your kit)

1. **Digital basics** → 01 Traffic Light, 03 Piano, 14 Relay  
2. **Analog & PWM** → 02 Dimmer, 07 Light Sensor  
3. **Motors** → 04 Servo, 05 Stepper  
4. **Displays** → 06 LCD, 12 Seven-segment, 15 NeoPixel  
5. **Sensors** → 08 Vibration, 09 NTC  
6. **Input devices** → 10 IR Remote, 11 Keypad  
7. **RFID foundation** → 13 RFID Basic  
8. **Capstone** → **16 RFID Door Lock** (combines almost everything)

After finishing project 16 you will have solid skills ready to move toward industrial automation (PLC, HMI, etc.).

---

## Getting Started

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install required libraries when needed (MFRC522, Keypad, IRremote, Adafruit NeoPixel…).
3. Select **Board: Arduino Uno** and the correct **Port**.
4. Open any project `.ino` → Upload.

Most projects run from USB power. For multiple motors or many NeoPixels consider an external 5 V supply.

---

## Conventions in every project README

1. Description  
2. Components (matched to BanLinhKien kit)  
3. Wiring (clear pin table / ASCII)  
4. Code explanation  
5. Upload & Run  
6. Extensions / next ideas

---

## License

MIT License — feel free to fork, learn, and build cool things.

Happy making! 🚀
