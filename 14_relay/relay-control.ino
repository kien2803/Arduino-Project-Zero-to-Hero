// 14 - Relay Mini 1 Channel
// Toggle relay every 2 seconds (simulate controlling a load)

int relayPin = 7;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // most modules are active LOW or HIGH - test
  Serial.begin(9600);
  Serial.println("Relay Ready");
}

void loop() {
  digitalWrite(relayPin, HIGH);
  Serial.println("Relay ON");
  delay(2000);

  digitalWrite(relayPin, LOW);
  Serial.println("Relay OFF");
  delay(2000);
}
