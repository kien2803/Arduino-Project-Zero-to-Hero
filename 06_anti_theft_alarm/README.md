# 06 — Anti-Theft Vibration Alarm

A simple alarm that triggers when someone moves or knocks the object it is attached to.

## What it does

When the vibration sensor detects a shock or movement, the LED lights up and the buzzer beeps.  
This is the basic principle behind many drawer alarms, bike alarms, and door vibration sensors.

## Components

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| Vibration / shock sensor module | 1 |
| Buzzer | 1 |
| LED (optional, pin 13 works) | 1 |

## Wiring

```
Vibration Sensor     Arduino
----------------     -------
VCC              --> 5V
GND              --> GND
DO               --> D2

Buzzer +         --> D8
Buzzer -         --> GND
```

Adjust the small potentiometer on the sensor board so that the sensor stays quiet when the table is still.

## Upload & Test

Upload the sketch, then gently tap the sensor or the table. You should hear a beep and see the LED flash.

## Extensions

- Add a delay so the alarm stays on for several seconds.
- Combine with RFID later so only an authorized card can disarm the alarm.
- Use a relay to trigger a louder siren or a light.
