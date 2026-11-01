/*
  Practical 4: Sending Sensor Data to Web/Cloud and Displaying on Web Page using ESP32
  Course: Computer Laboratory II - Industrial Internet of Things (417526)
  Department of AI & DS, ADYPSOE, SPPU
  Description: Reads analog sensor value from Potentiometer (GPIO 34) and hosts a real-time
  web dashboard on port 80 with 1-second auto-refresh (<meta http-equiv='refresh' content='1'>).
*/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int potPin = 34; // Potentiometer connected to GPIO 34 (ADC1_CH6)
int potValue = 0;      // Sensor reading variable

WebServer server(80);

void handleRoot() {
  potValue = analogRead(potPin); // Read live sensor value

  String webpage = "<!DOCTYPE html><html><head>";
  webpage += "<meta http-equiv='refresh' content='1'>"; // Auto-refresh page every 1 second
  webpage += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  webpage += "<title>ESP32 IIoT Sensor Monitor</title>";
  webpage += "<style>body{font-family:sans-serif;text-align:center;background:#0f172a;color:#f8fafc;padding-top:40px;}";
  webpage += ".gauge{display:inline-block;background:#1e293b;padding:30px 50px;border-radius:16px;box-shadow:0 8px 24px rgba(0,0,0,0.4);border:1px solid #334155;}";
  webpage += ".val{font-size:52px;font-weight:bold;color:#38bdf8;margin:16px 0;}";
  webpage += ".bar-box{width:260px;height:20px;background:#334155;border-radius:10px;overflow:hidden;margin:15px auto;}";
  int pct = map(potValue, 0, 4095, 0, 100);
  webpage += "<div class='gauge'><h1>Industrial IoT Live Sensor Monitor</h1>";
  webpage += "<h3>Potentiometer (Analog Pin 34)</h3>";
  webpage += "<div class='val'>" + String(potValue) + "</div>";
  webpage += "<div class='bar-box'><div style='height:100%;width:" + String(pct) + "%;background:#0284c7;'></div></div>";
  webpage += "<p>Status: " + String(potValue > 2000 ? "<span style='color:#ef4444;font-weight:bold;'>HIGH THRESHOLD WARNING</span>" : "<span style='color:#22c55e;'>NORMAL</span>") + "</p>";
  webpage += "<small>Auto-refreshes every 1 second</small>";
  webpage += "</div></body></html>";

  server.send(200, "text/html", webpage);
}

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("Web Server URL: http://");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("Web Server Started.");
}

void loop() {
  server.handleClient();
  delay(100);
}
