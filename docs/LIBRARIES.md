# Library Dependencies

Tested versions — the `lib_deps` in `platformio.ini` resolve to these.
Install by name in the Arduino IDE Library Manager.

| Library | Version | Projects | Notes |
|---------|---------|----------|-------|
| MFRC522 | 1.4.12 | 10, 11 | miguelbalboa — SPI RFID |
| Keypad | 3.1.1 | 08 | Mark Stanley / Alexander Brevig |
| IRremote | 4.7.1 | 07 | arduino-irremote — **v4 API**, not compatible with v2 sketches |
| Servo | 1.3.0 | 09, 11 | arduino-libraries |
| LiquidCrystal | 1.0.7 | 11 | arduino-libraries |
| SPI | core | 10, 11 | bundled with the AVR core |

## Version notes

- **IRremote 4.x** changed the API completely: `IrReceiver`,
  `decodedIRData`, `IRDATA_FLAGS_IS_REPEAT`. Old `IRrecv`/`decode_results`
  tutorials online are v2/v3 — don't mix.
- On **PlatformIO**, `Servo`/`LiquidCrystal` are registry packages
  (`arduino-libraries/…`), not bundled — that's why they're in
  `lib_deps`. In the Arduino IDE they're already built in.
- **MFRC522** requires SPI and the board's 3.3 V rail — see project 10.
