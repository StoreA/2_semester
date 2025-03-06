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
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFBjCCAu6gAwIBAgIRAIp9PhPWLzDvI4a9KQdrNPgwDQYJKoZIhvcNAQELBQAw\n" \
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n" \
"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMjQwMzEzMDAwMDAw\n" \
"WhcNMjcwMzEyMjM1OTU5WjAzMQswCQYDVQQGEwJVUzEWMBQGA1UEChMNTGV0J3Mg\n" \
"RW5jcnlwdDEMMAoGA1UEAxMDUjExMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB\n" \
"CgKCAQEAuoe8XBsAOcvKCs3UZxD5ATylTqVhyybKUvsVAbe5KPUoHu0nsyQYOWcJ\n" \
"DAjs4DqwO3cOvfPlOVRBDE6uQdaZdN5R2+97/1i9qLcT9t4x1fJyyXJqC4N0lZxG\n" \
"AGQUmfOx2SLZzaiSqhwmej/+71gFewiVgdtxD4774zEJuwm+UE1fj5F2PVqdnoPy\n" \
"6cRms+EGZkNIGIBloDcYmpuEMpexsr3E+BUAnSeI++JjF5ZsmydnS8TbKF5pwnnw\n" \
"SVzgJFDhxLyhBax7QG0AtMJBP6dYuC/FXJuluwme8f7rsIU5/agK70XEeOtlKsLP\n" \
"Xzze41xNG/cLJyuqC0J3U095ah2H2QIDAQABo4H4MIH1MA4GA1UdDwEB/wQEAwIB\n" \
"hjAdBgNVHSUEFjAUBggrBgEFBQcDAgYIKwYBBQUHAwEwEgYDVR0TAQH/BAgwBgEB\n" \
"/wIBADAdBgNVHQ4EFgQUxc9GpOr0w8B6bJXELbBeki8m47kwHwYDVR0jBBgwFoAU\n" \
"ebRZ5nu25eQBc4AIiMgaWPbpm24wMgYIKwYBBQUHAQEEJjAkMCIGCCsGAQUFBzAC\n" \
"hhZodHRwOi8veDEuaS5sZW5jci5vcmcvMBMGA1UdIAQMMAowCAYGZ4EMAQIBMCcG\n" \
"A1UdHwQgMB4wHKAaoBiGFmh0dHA6Ly94MS5jLmxlbmNyLm9yZy8wDQYJKoZIhvcN\n" \
"AQELBQADggIBAE7iiV0KAxyQOND1H/lxXPjDj7I3iHpvsCUf7b632IYGjukJhM1y\n" \
"v4Hz/MrPU0jtvfZpQtSlET41yBOykh0FX+ou1Nj4ScOt9ZmWnO8m2OG0JAtIIE38\n" \
"01S0qcYhyOE2G/93ZCkXufBL713qzXnQv5C/viOykNpKqUgxdKlEC+Hi9i2DcaR1\n" \
"e9KUwQUZRhy5j/PEdEglKg3l9dtD4tuTm7kZtB8v32oOjzHTYw+7KdzdZiw/sBtn\n" \
"UfhBPORNuay4pJxmY/WrhSMdzFO2q3Gu3MUBcdo27goYKjL9CTF8j/Zz55yctUoV\n" \
"aneCWs/ajUX+HypkBTA+c8LGDLnWO2NKq0YD/pnARkAnYGPfUDoHR9gVSp/qRx+Z\n" \
"WghiDLZsMwhN1zjtSC0uBWiugF3vTNzYIEFfaPG7Ws3jDrAMMYebQ95JQ+HIBD/R\n" \
"PBuHRTBpqKlyDnkSHDHYPiNX3adPoPAcgdF3H2/W0rmoswMWgTlLn1Wu0mrks7/q\n" \
"pdWfS6PJ1jty80r2VKsM/Dj3YIDfbjXKdaFU5C+8bhfJGqU3taKauuz0wHVGT3eo\n" \
"6FlWkWYtbt4pgdamlwVeZEW+LM7qZEJEsMNPrfC03APKmZsJgpWCDWOKZvkZcvjV\n" \
"uYkQ4omYCTX5ohy+knMjdOmdH9c7SpqEWBDC86fiNex+O0XOMEZSa8DA\n" \
"-----END CERTIFICATE-----\n";

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