// 04 - Automatic Night Light (4-pin RGB LED)
// Turns on a soft warm light when the environment becomes dark

const int lightPin = A0;     // Light sensor (analog)

// 4-pin RGB LED pins (change if your wiring is different)
const int redPin   = 9;
const int greenPin = 10;
const int bluePin  = 11;

// Set to true if your RGB LED is Common Anode (common pin to 5V)
// Set to false if Common Cathode (common pin to GND)
const bool COMMON_ANODE = false;

const int threshold = 400;   // Adjust this value to your room

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  turnOff();
  Serial.begin(9600);
  Serial.println("Automatic Night Light (RGB) ready");
}

void setColor(int r, int g, int b) {
  if (COMMON_ANODE) {
    // For common anode: LOW = on, HIGH = off
    analogWrite(redPin,   255 - r);
    analogWrite(greenPin, 255 - g);
    analogWrite(bluePin,  255 - b);
  } else {
    // For common cathode: HIGH = on
    analogWrite(redPin,   r);
    analogWrite(greenPin, g);
    analogWrite(bluePin,  b);
  }
}

void turnOff() {
  setColor(0, 0, 0);
}

void loop() {
  int lightLevel = analogRead(lightPin);
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  if (lightLevel < threshold) {
    // Dark → soft warm white / orange night light
    // You can change these values to any color you like
    setColor(180, 40, 0);      // warm orange
    // setColor(255, 80, 20);  // brighter warm
    // setColor(0, 0, 80);     // soft blue
  } else {
    turnOff();
  }

  delay(200);
}
