# Library Dependencies

Tested versions — the `lib_deps` in `platformio.ini` resolve to these.
Install by name in the Arduino IDE Library Manager.

| Library | Version | Projects | Notes |
|---------|---------|----------|-------|
| MFRC522 | 1.4.12 | 10, 11 | miguelbalboa — SPI RFID |
| Adafruit_NeoPixel | 1.12.x | 07, 10, 11 | WS2812 ring driver |
| IRremote | 4.7.1 | 07, 11 | arduino-irremote — **v4 API**, not compatible with v2 sketches |
| Servo | 1.3.0 | 11 | arduino-libraries |
| LiquidCrystal | 1.0.7 | 11 | arduino-libraries |
| SPI | core | 10, 11 | bundled with the AVR core |

No library needed for: `shiftOut()` (74HC595), 7-segment multiplexing,
and the 28BYJ-48 coil sequence — those are taught raw on purpose.

## Version notes

- **IRremote 4.x** changed the API completely: `IrReceiver`,
  `decodedIRData`, `IRDATA_FLAGS_IS_REPEAT`. Old `IRrecv`/`decode_results`
  tutorials online are v2/v3 — don't mix.
- On **PlatformIO**, `Servo`/`LiquidCrystal` are registry packages
  (`arduino-libraries/…`), not bundled — that's why they're in
  `lib_deps`. In the Arduino IDE they're already built in.
- **MFRC522** requires SPI and the board's 3.3 V rail — see project 10.
