
#include <Arduino.h>
#include <WiFi.h>
#include "sensors/dht22.h"
#include "sensors/mhz19b.h"
#include "leds/ws2812b.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";
const char* wifiHostName = "";

const char* mqtt_server = "joel-telegraf";

WiFiClient espClient;
Dht22 dht22;
Mhz19b mhz19b;
WS2812b ws2812b;
PubSubClient client(espClient);

void setup() {
  // Begin serial and setup sensors
  Serial.begin(115200);
  dht22.setup();
  mhz19b.setup();
  ws2812b.setup();

  delay(10);

  // Setup wifi connection
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  // Setup mqtt connection
  client.setServer(mqtt_server, 1883);

  delay(10000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("joel-sense-1")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(5000);

  float h = dht22.readHumidity();
  float t = dht22.readTemperature();
  int co2 = mhz19b.readCO2();

  if (dht22.verify(t) || dht22.verify(h)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else if(mhz19b.verify()) {
    Serial.println("Failed to read from MHZ19 sensor!"); 
  }
  else {
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["temperature"] = t;
    jsonDocument["humidity"] = h;
    jsonDocument["co2"] = co2;
    
    serializeJson(jsonDocument, Serial);
  
    String json_value;
    serializeJson(jsonDocument, json_value);

    if(co2 >= 1000) {
      ws2812b.loop();
    }
  
    char mqtt_value[200];
    json_value.toCharArray(mqtt_value, 200);
    
    client.publish("/joel-sense-1/sensor", mqtt_value, true);
  }
}
