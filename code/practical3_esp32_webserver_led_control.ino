/*
  Practical 3: Web Interface to Monitor and Control LEDs using ESP32 (Cyber-Physical System)
  Course: Computer Laboratory II - Industrial Internet of Things (417526)
  Department of AI & DS, ADYPSOE, SPPU
  Description: Hosts an HTTP WebServer on port 80 using ESP32 Wi-Fi.
  Provides interactive HTML controls to turn Red LED (GPIO 12) and Green LED (GPIO 14) ON and OFF.
*/

#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi network credentials (replace with your Hotspot / Wi-Fi credentials or "Wokwi-GUEST" for simulator)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80); // Create WebServer instance on standard HTTP port 80

int redLED = 12;   // Red LED connected to GPIO 12 (via 220-ohm resistor)
int greenLED = 14; // Green LED connected to GPIO 14 (via 220-ohm resistor)

void setup() {
  Serial.begin(115200);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);

  Serial.println("\nConnecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected successfully!");
  Serial.print("ESP32 Web Server IP Address: http://");
  Serial.println(WiFi.localIP());

  // Define HTTP Route Handlers
  server.on("/", []() {
    String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<style>body{font-family:Arial,sans-serif;text-align:center;margin-top:40px;background:#f4f6f9;}";
    html += ".btn{display:inline-block;padding:12px 24px;margin:8px;font-size:18px;text-decoration:none;border-radius:6px;color:#fff;}";
    html += ".btn-on{background:#28a745;} .btn-off{background:#dc3545;} .card{background:#fff;padding:24px;max-width:400px;margin:auto;border-radius:10px;box-shadow:0 4px 10px rgba(0,0,0,0.1);}</style></head>";
    html += "<body><div class='card'><h2>ESP32 CPS LED Control</h2>";
    html += "<p><strong>Red LED (GPIO 12):</strong><br>";
    html += "<a class='btn btn-on' href='/red/on'>ON</a> <a class='btn btn-off' href='/red/off'>OFF</a></p>";
    html += "<p><strong>Green LED (GPIO 14):</strong><br>";
    html += "<a class='btn btn-on' href='/green/on'>ON</a> <a class='btn btn-off' href='/green/off'>OFF</a></p>";
    html += "</div></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/red/on", []() {
    digitalWrite(redLED, HIGH);
    Serial.println("Command: Red LED -> ON");
    server.send(200, "text/plain", "Red LED is ON. <a href='/'>Back</a>");
  });

  server.on("/red/off", []() {
    digitalWrite(redLED, LOW);
    Serial.println("Command: Red LED -> OFF");
    server.send(200, "text/plain", "Red LED is OFF. <a href='/'>Back</a>");
  });

  server.on("/green/on", []() {
    digitalWrite(greenLED, HIGH);
    Serial.println("Command: Green LED -> ON");
    server.send(200, "text/plain", "Green LED is ON. <a href='/'>Back</a>");
  });

  server.on("/green/off", []() {
    digitalWrite(greenLED, LOW);
    Serial.println("Command: Green LED -> OFF");
    server.send(200, "text/plain", "Green LED is OFF. <a href='/'>Back</a>");
  });

  server.begin(); // Start HTTP Server
  Serial.println("HTTP Web Server Started.");
}

void loop() {
  server.handleClient(); // Listen and handle client browser requests
}
