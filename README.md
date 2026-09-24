# Arduino Project Zero to Hero

A practical learning path that turns everyday objects into simple Arduino projects.  
Start with a traffic light and finish with a complete smart door lock — all built from common kit parts.

> **Philosophy:** Real products first. Theory follows naturally.

---

## Project Roadmap (Easy → Hard)

| # | Project | Real-life product | Difficulty | Main skills |
|---|---------|-------------------|------------|-------------|
| 01 | [Traffic Light](./01_traffic_light/) | Intersection traffic light | 🟢 Easy | Digital output, sequencing |
| 02 | [Dimmer Lamp](./02_dimmer_led/) | Adjustable desk lamp | 🟢 Easy | Analog input, PWM |
| 03 | [Mini Piano](./03_piano/) | Toy piano / doorbell | 🟢 Easy | Buttons, tone generation |
| 04 | [Automatic Night Light](./04_night_light/) | Corridor night light | 🟢 Easy | Light sensor, threshold |
| 05 | [Room Thermometer](./05_thermometer/) | Digital room thermometer | 🟡 Medium | NTC sensor, calculation, display |
| 06 | [Anti-Theft Alarm](./06_anti_theft_alarm/) | Simple vibration alarm | 🟡 Medium | Digital sensor, buzzer |
| 07 | [Remote Controlled Lamp](./07_remote_lamp/) | IR remote lamp / socket | 🟡 Medium | IR receiver, relay |
| 08 | [Password Lock](./08_password_lock/) | Keypad door lock | 🟡 Medium | Keypad, state machine |
| 09 | [Servo Barrier Gate](./09_servo_barrier/) | Parking barrier / gate | 🟡 Medium | Servo control |
| 10 | [RFID Access Control](./10_rfid_access/) | Card access system | 🔶 Medium-Hard | RFID, UID checking |
| 11 | [Smart Door Lock](./11_smart_door_lock/) | Full smart lock (RFID + Keypad + LCD + Servo) | 🔴 Hard | System integration |

See **[COMPONENTS.md](./COMPONENTS.md)** for the recommended parts list.

---

## Learning Philosophy

Each project is designed as a **real product** you might find at home or in a small office:

- You first see *what* it does (the product).
- Then you learn *how* it works (the code + wiring).
- Finally you get ideas to improve it (extensions).

By the end of project 11 you will have built a complete access-control system and understand how many commercial products are actually put together.

---

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Connect your Arduino Uno.
3. Open any project folder → open the `.ino` file → Upload.

Required libraries (install via Library Manager when needed):
- MFRC522
- Keypad
- IRremote
- Servo (built-in)
- LiquidCrystal (built-in)

---

## License

MIT License. Fork it, improve it, share it.

Happy building!
