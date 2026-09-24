// 09 - NTC Thermistor Module
// Read temperature and display on Serial (can be extended to LCD)

const int ntcPin = A0;
const float BETA = 3950;      // Beta coefficient of the thermistor (typical)
const float T0 = 298.15;      // 25°C in Kelvin
const float R0 = 10000;       // 10k NTC at 25°C
const float SERIES_R = 10000; // usually the module has a 10k divider

void setup() {
  Serial.begin(9600);
  Serial.println("NTC Temperature Module Ready");
}

void loop() {
  int adc = analogRead(ntcPin);
  float voltage = adc * (5.0 / 1023.0);
  float resistance = SERIES_R * ((5.0 / voltage) - 1);   // voltage divider formula

  // Steinhart-Hart simplified (Beta equation)
  float temperatureK = 1.0 / ( (1.0 / T0) + (1.0 / BETA) * log(resistance / R0) );
  float temperatureC = temperatureK - 273.15;

  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print("  |  Temp: ");
  Serial.print(temperatureC, 1);
  Serial.println(" °C");

  delay(1000);
}
