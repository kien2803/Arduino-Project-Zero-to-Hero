// 05 - Room Thermometer
// Reads temperature from an NTC module and prints it on Serial.
//
// Divider orientation assumed here (most 10k NTC modules):
//
//   5V ---[ NTC ]---+---[ 10k fixed ]--- GND
//                   |
//                   A0
//
// With this layout V(A0) rises as the NTC heats up and
//   R_ntc = SERIES_R * (Vcc / Vout - 1).
// If your module is wired the other way (NTC to GND), readings
// will move backwards — see README "Troubleshooting".

const int ntcPin = A0;

// Typical values for many 10k NTC modules
const float BETA      = 3950.0;
const float T0        = 298.15;   // 25 °C in Kelvin
const float R0        = 10000.0;  // NTC resistance at 25 °C
const float SERIES_R  = 10000.0;  // fixed divider resistor

const int SAMPLES = 8;            // average a few readings to reduce noise

void setup() {
  Serial.begin(9600);
  Serial.println("Room Thermometer ready");
  Serial.println("Temp (C)");
}

int readAdc() {
  long sum = 0;
  for (int i = 0; i < SAMPLES; i++) sum += analogRead(ntcPin);
  return (int)(sum / SAMPLES);
}

void loop() {
  int adc = readAdc();

  // Guard rails: the ADC rails mean the divider node is open or shorted.
  // Without these checks the math below divides by zero / logs a non-positive.
  if (adc <= 0) {
    Serial.println("ERROR: ADC=0 — A0 at GND. Check wiring (short / no sensor).");
    delay(1000);
    return;
  }
  if (adc >= 1023) {
    Serial.println("ERROR: ADC=1023 — A0 at VCC. Check wiring (open circuit).");
    delay(1000);
    return;
  }

  float voltage    = adc * (5.0 / 1023.0);
  float resistance = SERIES_R * (5.0 / voltage - 1.0);

  float steinhart    = log(resistance / R0) / BETA + 1.0 / T0;
  float temperatureC = (1.0 / steinhart) - 273.15;

  // Sanity range for a room thermometer; outside it the divider is
  // probably oriented the other way or SERIES_R/BETA is wrong.
  if (temperatureC < -40.0 || temperatureC > 125.0) {
    Serial.print("Implausible reading: ");
    Serial.println(temperatureC, 1);
  } else {
    Serial.println(temperatureC, 1);
  }
  delay(1000);
}
