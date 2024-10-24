#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Mina.W";
const char* password = "12345678";

WebServer server(80);

// Variables to store sensor data received from Arduino
float temperature = 0.0;
float humidity = 0.0;
float heartRate = 0.0;
int noiseLevel = 20;  // Assuming noise level is measured by ESP32
int weight = 5;       // Assuming weight is measured by ESP32

void setup() {
  Serial.begin(9600);  // Serial connection to Arduino
  WiFi.begin(ssid, password);

  // Connecting to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  Serial.println(WiFi.localIP());

  // Define HTTP routes
  server.on("/", handleRoot);
  server.on("/readings", handleSensorReadings);
  
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");  // CORS header
  server.send(200, "text/plain", "Welcome to the ESP Server");
}

void handleSensorReadings() {
  server.sendHeader("Access-Control-Allow-Origin", "*");  // CORS header

  // Create JSON string from sensor data
  String jsonData = "{\"temperature\": " + String(temperature, 2) +  // Display 2 decimal places
                    ", \"humidity\": " + String(humidity, 2) +
                    ", \"heartRate\": " + String(heartRate, 2) +
                    ", \"weight\": " + String(weight) +
                    ", \"noiseLevel\": " + String(noiseLevel) + "}";

  server.send(200, "application/json", jsonData);
}

void loop() {
  server.handleClient();  // Handle incoming HTTP requests

  // Check if data is available on the Serial port
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // Read incoming data line by line
    
    // Parse the incoming data based on labels (e.g., "heartbeat", "temp", "hum")
    if (data.startsWith("heartbeat: ")) {
      heartRate = data.substring(data.indexOf(": ") + 2).toFloat();
    } else if (data.startsWith("temp: ")) {
      temperature = data.substring(data.indexOf(": ") + 2).toFloat();
    } else if (data.startsWith("hum: ")) {
      humidity = data.substring(data.indexOf(": ") + 2).toFloat();
    }

    // Print received data for debugging
    Serial.println("Updated readings:");
    Serial.println("Heartbeat: " + String(heartRate));
    Serial.println("Temperature: " + String(temperature));
    Serial.println("Humidity: " + String(humidity));
  }
}
