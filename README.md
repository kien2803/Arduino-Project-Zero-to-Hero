# Arduino Project Zero to Hero

A structured embedded curriculum that goes from blinking an LED to autonomous robotics.  
**Phase 1** (this repo): 11 Arduino projects from a traffic light to a complete smart door lock.

> **Philosophy:** Real products first. Theory follows naturally.

---

## Phase 1 — Arduino Fundamentals (Easy → Hard)

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

**Phase 2 — Robotics Fundamentals** and **Phase 3 — Intelligent
Robotics** (DC motors, line tracking, encoders, PID, sensor fusion) are
designed in **[ROADMAP.md](./ROADMAP.md)**.

See **[COMPONENTS.md](./COMPONENTS.md)** for the parts list and
**[docs/](./docs/)** for library versions + simulation notes.

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

Required libraries (install via Library Manager — see [docs/LIBRARIES.md](./docs/LIBRARIES.md) for tested versions):
- MFRC522, Keypad, IRremote (≥ 4.x)
- Servo, LiquidCrystal (built-in in the IDE; registry packages on PlatformIO)

---

## Flashing without the Arduino IDE

### Option 1 — GUI app (easiest, download & run)

Grab `arduino-flasher` from [Releases](../../releases), then:

```bash
chmod +x arduino-flasher
./arduino-flasher
```

Pick a lesson → pick the board port → **Upload**. The binary bundles the
prebuilt hex files, avrdude, and a pure-Python uploader — nothing else to
install. (Linux x86_64. One-time step if you get a port permission error:
`sudo usermod -aG dialout $USER`, then log out/in.)

### Option 2 — `flasher.py` from this repo

```bash
./flasher.py            # GUI (needs python3-tkinter + pyserial)
./flasher.py --cli      # terminal menu instead
```

### Option 3 — `flash.sh` terminal picker

```bash
./flash.sh            # interactive menu (uses fzf if installed)
./flash.sh 03_piano   # flash a specific lesson directly
```

Requirements on the flashing machine:

- `avrdude` (`sudo dnf install avrdude` / `sudo apt install avrdude`). If `arduino-cli` is installed, its bundled avrdude is used automatically.
- `platformio` (`pip install --user platformio`) to compile sketches at flash time. Without it, the prebuilt `build/*.hex` files are flashed instead — rebuild them any time with `./build.sh`.

The board is auto-detected on `/dev/ttyACM*` or `/dev/ttyUSB*` (override with `PORT=/dev/ttyXXX`). If you get a permission error on the port: `sudo usermod -aG dialout $USER`, then log out and back in.

---

## License

MIT License. Fork it, improve it, share it.

Happy building!
