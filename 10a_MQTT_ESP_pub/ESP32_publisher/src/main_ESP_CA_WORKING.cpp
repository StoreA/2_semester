#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// Function declarations
void setup_wifi();
void maintain_wifi();

const char* ssid = "TP-Link_6B21";        // Your hotspot SSID
const char* password = "Albatros1920JaTak!"; // Your hotspot password

// MQTT Broker details
const char* mqtt_server = "74c7d5bfb46248ca858248f3b31bb752.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "anders";
const char* mqtt_pass = "Mortensen123!"; // Add your actual password here
const char* mqtt_topic_temp = "temp3";
const char* mqtt_topic_humi = "humi";
const char* clientID = "ESP32_DHT11";

// Let's Encrypt R11 CA Certificate
const char* ca_cert = "../certs/ca.crt";

// DHT11 settings
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// WiFi and MQTT clients
WiFiClientSecure espClient;
PubSubClient client(espClient);

// Timing variables
unsigned long previousMillis = 0;
const long interval = 500;
unsigned long lastWifiCheck = 0;
const long wifiCheckInterval = 5000; // Check WiFi every 5 seconds when disconnected

// Callback function to make monitor on ESP32 what is published in ASCII
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  Serial.print("Message (ASCII): ");
  for (int i = 0; i < length; i++) {
    if (payload[i] >= 32 && payload[i] <= 126) {
      Serial.print((char) payload[i]);
    } else {
      Serial.print('.');
    }
  }
  Serial.println();
  
  Serial.print("Message (hex): ");
  for (int i = 0; i < length; i++) {
    if (payload[i] < 16) Serial.print("0");
    Serial.print(payload[i], HEX);
    if (i < length - 1) Serial.print(" ");
  }
  Serial.println();
  Serial.println("-----------------------");
}

void setup() {
  Serial.begin(115200);
  
  dht.begin();
  
  setup_wifi();
  
  espClient.setCACert(ca_cert);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // Runs ASCII for message published
}

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Failed to connect to WiFi initially");
  }
}

void maintain_wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastWifiCheck >= wifiCheckInterval) {
      lastWifiCheck = currentMillis;
      Serial.print("WiFi disconnected, attempting to reconnect to ");
      Serial.println(ssid);
      
      WiFi.disconnect();  // Clean up previous connection attempt
      WiFi.begin(ssid, password);
      
      int attempts = 0;
      while (WiFi.status() != WL_CONNECTED && attempts < 10) { // 5-second attempt
        delay(500);
        Serial.print(".");
        attempts++;
      }
      
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi reconnected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
      }
    }
  }
}

void reconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No WiFi - skipping MQTT");
    return;
  }

  if (!client.connected()) {
    Serial.print("Attempting MQTT connection with clientID: ");
    Serial.println(clientID);
    
    if (client.connect(clientID, mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      
      // Subscribing the ESP32 to the internal topics in order to receive callback
      client.subscribe(mqtt_topic_temp);
      client.subscribe(mqtt_topic_humi);
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000); // Add delay to prevent rapid retry loops
    }
  }
}

void loop() {
  // Maintain WiFi connection
  maintain_wifi();

  // Maintain MQTT connection
  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }

  // Sensor reading and publishing
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval && WiFi.status() == WL_CONNECTED) {
    previousMillis = currentMillis;
    
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    char temp_payload[20];
    char humi_payload[20];
    snprintf(temp_payload, sizeof(temp_payload), "%.1f", temperature);
    snprintf(humi_payload, sizeof(humi_payload), "%.1f", humidity);

    // Serial.print("Publishing temperature: ");
    // Serial.println(temp_payload);
    if (client.connected()) {
      if (client.publish(mqtt_topic_temp, temp_payload)) {
        // Multiple static serial prints instead of string print to avoid fragmentation
        Serial.println("Success publishing ");
        Serial.println(mqtt_topic_temp);
        Serial.println(temp_payload);

        // Serial.println(String("Succes publishing ") + mqtt_topic_temp);
      }
      else 
      {
        Serial.println("Failed to send ");
        Serial.println(mqtt_topic_temp);

        // Serial.println(String("Failed to send ") + mqtt_topic_temp);
      }
    }

    // Serial.print("Publishing humidity: ");
    // Serial.println(humi_payload);
    if (client.connected()) {
      if (client.publish(mqtt_topic_humi, humi_payload)) {
        // Using multiple static prints instead of string to not fragment memory
        Serial.println("Success publishing ");
        Serial.println(mqtt_topic_humi);
        Serial.println(humi_payload);


        // Serial.println(String("Success publishing ") + mqtt_topic_humi);
      }
      else {
        // Same as before, multiple statics
        Serial.println("Failed to send ");
        Serial.println(mqtt_topic_humi);

        // Serial.println(String("Failed to send ") + mqtt_topic_humi);
      }
    }
  }
}