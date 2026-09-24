// 05 - Room Thermometer
// Reads temperature from NTC module and shows it on Serial (easy to extend to LCD)

const int ntcPin = A0;

// Typical values for many 10k NTC modules
const float BETA = 3950.0;
const float T0   = 298.15;   // 25°C in Kelvin
const float R0   = 10000.0;  // resistance at 25°C
const float SERIES_R = 10000.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Room Thermometer ready");
  Serial.println("Temp (C)");
}

void loop() {
  int adc = analogRead(ntcPin);
  float voltage = adc * (5.0 / 1023.0);
  float resistance = SERIES_R * (5.0 / voltage - 1.0);

  float steinhart = log(resistance / R0) / BETA + 1.0 / T0;
  float temperatureC = (1.0 / steinhart) - 273.15;

  Serial.println(temperatureC, 1);
  delay(1000);
}
