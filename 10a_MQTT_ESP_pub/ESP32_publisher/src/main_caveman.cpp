// #include <WiFi.h>
// #include <AsyncMqttClient.h>  // Marvin Roger's AsyncMqttClient
// #include <DHT.h>

// #define DHTPIN 4
// #define DHTTYPE DHT11

// const char* ssid = "TP-Link_6B21";
// const char* password = "Albatros1920JaTak!";
// const char* mqtt_broker_ip = "192.168.0.62";
// const int mqtt_port = 8883;
// const char* mqtt_topic = "temp3";
// const char* mqtt_username = "anders";
// const char* mqtt_password = "morten";

// AsyncMqttClient mqttClient;
// WiFiClient wifiClient;  // For raw TCP test
// DHT dht(DHTPIN, DHTTYPE);

// volatile bool mqttConnected = false;

// void connectToWiFi() {
//   Serial.print("Connecting to WiFi...");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nWiFi connected");
//   Serial.print("IP Address: ");
//   Serial.println(WiFi.localIP());
//   Serial.print("RSSI (signal strength): ");
//   Serial.println(WiFi.RSSI());
// }

// void testRawTCP() {
//   Serial.println("Testing raw TCP connection to 8.8.8.8:80 (Google DNS)");
//   if (wifiClient.connect("8.8.8.8", 80)) {
//     Serial.println("Raw TCP connection succeeded!");
//     wifiClient.stop();
//   } else {
//     Serial.println("Raw TCP connection failed!");
//     Serial.print("WiFi status: ");
//     Serial.println(WiFi.status());
//   }
// }

// void onMqttConnect(bool sessionPresent) {
//   Serial.println("Connected to MQTT broker!");
//   Serial.print("Session present: ");
//   Serial.println(sessionPresent);
//   mqttConnected = true;
  
//   uint16_t packetIdSub = mqttClient.subscribe(mqtt_topic, 0);
//   Serial.print("Subscribing to topic, packetId: ");
//   Serial.println(packetIdSub);
// }

// void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
//   Serial.print("Disconnected from MQTT broker! Reason: ");
//   switch (reason) {
//     case AsyncMqttClientDisconnectReason::TCP_DISCONNECTED:
//       Serial.println("TCP Disconnected");
//       break;
//     case AsyncMqttClientDisconnectReason::MQTT_UNACCEPTABLE_PROTOCOL_VERSION:
//       Serial.println("Unacceptable Protocol Version");
//       break;
//     case AsyncMqttClientDisconnectReason::MQTT_IDENTIFIER_REJECTED:
//       Serial.println("Identifier Rejected");
//       break;
//     case AsyncMqttClientDisconnectReason::MQTT_SERVER_UNAVAILABLE:
//       Serial.println("Server Unavailable");
//       break;
//     case AsyncMqttClientDisconnectReason::MQTT_MALFORMED_CREDENTIALS:
//       Serial.println("Malformed Credentials");
//       break;
//     case AsyncMqttClientDisconnectReason::MQTT_NOT_AUTHORIZED:
//       Serial.println("Not Authorized");
//       break;
//     default:
//       Serial.println("Unknown");
//       break;
//   }
//   mqttConnected = false;
// }

// void onMqttPublish(uint16_t packetId) {
//   Serial.print("Publish acknowledged, packetId: ");
//   Serial.println(packetId);
// }

// void connectToMQTT() {
//   if (WiFi.status() == WL_CONNECTED && !mqttConnected) {
//     Serial.print("Attempting MQTT connection to ");
//     Serial.print(mqtt_broker_ip);
//     Serial.print(":");
//     Serial.println(mqtt_port);
//     mqttClient.connect();
//   } else if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("WiFi not connected, cannot connect to MQTT");
//   }
// }

// void setup() {
//   Serial.begin(115200);
  
//   WiFi.setTxPower(WIFI_POWER_19_5dBm);
//   connectToWiFi();
  
//   // Test raw TCP connection first
//   testRawTCP();
  
//   mqttClient.onConnect(onMqttConnect);
//   mqttClient.onDisconnect(onMqttDisconnect);
//   mqttClient.onPublish(onMqttPublish);
//   mqttClient.setServer(mqtt_broker_ip, mqtt_port);
//   mqttClient.setCredentials(mqtt_username, mqtt_password);
//   mqttClient.setClientId(("esp32-" + String(WiFi.macAddress())).c_str());
//   mqttClient.setKeepAlive(60);
  
//   connectToMQTT();
//   dht.begin();
// }

// void loop() {
//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("WiFi disconnected, attempting to reconnect...");
//     connectToWiFi();
//   }

//   if (!mqttConnected) {
//     connectToMQTT();
//     delay(5000);
//     return;
//   }

//   float temperature = dht.readTemperature();
//   float humidity = dht.readHumidity();

//   if (isnan(temperature) || isnan(humidity)) {
//     Serial.println("Failed to read from DHT sensor!");
//     delay(2000);
//     return;
//   }

//   String payload = "Temperature: " + String(temperature) + " C, Humidity: " + String(humidity) + " %";
//   if (mqttConnected) {
//     uint16_t packetIdPub = mqttClient.publish(mqtt_topic, 0, false, payload.c_str());
//     Serial.print("Publishing to ");
//     Serial.print(mqtt_topic);
//     Serial.print(", packetId: ");
//     Serial.println(packetIdPub);
//   } else {
//     Serial.println("Cannot publish - MQTT not connected");
//   }

//   Serial.println(payload);
//   delay(2000);
// }