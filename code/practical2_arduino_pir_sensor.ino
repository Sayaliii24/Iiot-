/*
  Practical 2: Interfacing PIR Sensor with Arduino & LED Indication
  Course: Computer Laboratory II - Industrial Internet of Things (417526)
  Department of AI & DS, ADYPSOE, SPPU
  Description: Reads digital state from PIR motion sensor (Pin 2).
  Turns ON LED (Pin 13) when motion is detected; turns OFF when no motion.
*/

int pirPin = 2;  // PIR Sensor OUT pin connected to Digital Pin 2
int ledPin = 13; // LED positive terminal (via 220-ohm resistor) to Pin 13

void setup() {
  pinMode(pirPin, INPUT);   // Configure PIR sensor pin as Digital INPUT
  pinMode(ledPin, OUTPUT);  // Configure LED pin as Digital OUTPUT
  Serial.begin(9600);       // Initialize Serial Communication at 9600 baud
  Serial.println("--- PIR Motion Sensor System Initializing (allowing warm-up) ---");
  delay(2000);              // PIR sensor warm-up delay
}

void loop() {
  int motionState = digitalRead(pirPin); // Read digital status: HIGH (Motion) or LOW (No motion)

  if (motionState == HIGH) {
    digitalWrite(ledPin, HIGH);          // Turn ON LED
    Serial.println("Motion detected!");
  } else {
    digitalWrite(ledPin, LOW);           // Turn OFF LED
    Serial.println("No motion detected");
  }

  delay(1000); // 1-second interval between checks
}
