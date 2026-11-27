/*
  PROJECT 04: AUTOMATIC NIGHT LIGHT (USING HIGH-SENSITIVITY ANALOG)
  - MS-CDS05: VCC -> 5V | GND -> GND | A0 -> A0
  - LED: Positive pin (+) -> 220R Resistor -> Pin 9
*/

const int LDR_AO_PIN = A0; 
const int LED_PIN = 9;    

// === ADJUST SENSITIVITY HERE ===
// The higher/lower the number, the more the sensitivity changes (Range from 0 to 1023)
int threshold = 900; 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== STARTING REAL-TIME LIGHT MEASUREMENT ===");
}

void loop() {
  // Read specific light level value (0 - 1023)
  int lightValue = analogRead(LDR_AO_PIN);
  
  Serial.print("Current light level: ");
  Serial.print(lightValue);

  // If light crosses the threshold (you may need to change > to < depending on the module)
  if (lightValue > threshold) { 
    Serial.println(" ---> DARK: Turn on light!");
    digitalWrite(LED_PIN, HIGH);
  } else {
    Serial.println(" ---> BRIGHT: Turn off light!");
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(300);
}
