int buzzerPin = 9;

int Do  = 2; 
int Re  = 3; 
int Mi  = 4; 
int Sol = 5;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(Do, INPUT_PULLUP);
  pinMode(Re, INPUT_PULLUP);
  pinMode(Mi, INPUT_PULLUP);
  pinMode(Sol, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(Do) == LOW) {
    tone(buzzerPin, 262); 
  } 
  else if (digitalRead(Re) == LOW) {
    tone(buzzerPin, 294); 
  } 
  else if (digitalRead(Mi) == LOW) {
    tone(buzzerPin, 330); 
  } 
  else if (digitalRead(Sol) == LOW) {
    tone(buzzerPin, 392); 
  }
  else {
    noTone(buzzerPin);   
  }
}