/*
  Practical 1: Alert System using ESP32 and Potentiometer
  Course: Computer Laboratory II - Industrial Internet of Things (417526)
  Department of AI & DS, ADYPSOE, SPPU
  Description: Reads analog voltage from a 10K potentiometer connected to GPIO 34.
  If the reading exceeds threshold 2000, triggers a "warning" message to Serial Monitor.
*/

const int potPin = 34; // GPIO 34 (ADC1_CH6) connected to Potentiometer Wiper (SIG)
int potValue = 0;      // Variable to store ADC reading (0 - 4095)

void setup() {
  Serial.begin(115200); // Initialize Serial Monitor at 115200 baud
  delay(1000);          // Allow board stabilization
  Serial.println("--- ESP32 Potentiometer Alert System Initialized ---");
}

void loop() {
  potValue = analogRead(potPin); // Read 12-bit ADC value (0 to 4095)

  // Check if threshold exceeded
  if (potValue > 2000) {
    Serial.println("WARNING! Potentiometer threshold exceeded (>2000)");
  }

  // Display continuous sensor value
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  delay(500); // 500ms delay between readings (2 updates per second)
}
