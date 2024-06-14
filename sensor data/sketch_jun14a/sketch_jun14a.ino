#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4      // Pin yang terhubung ke data pin DHT11
#define DHTTYPE DHT11 // DHT 11

const char* ssid = "mawar";
const char* password = "aina1209";

const char* serverName = "http://192.168.100.183:5000/data";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);
  dht.begin();
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    String serverPath = serverName;
    http.begin(serverPath.c_str());
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"temperature\":\"" + String(t) + "\",\"humidity\":\"" + String(h) + "\"}";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  
  delay(60000); // Mengirim data setiap 60 detik
}
