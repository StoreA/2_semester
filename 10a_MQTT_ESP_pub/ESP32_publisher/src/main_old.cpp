// #include <WiFi.h>
// #include <AsyncMqttClient.h>
// #include <Ticker.h>
// #include <DHT.h>
// #include <ESP32Ping.h>

// // WiFi Credentials
// #define WIFI_SSID "TP-Link_6B21"
// #define WIFI_PASSWORD "Albatros1920JaTak!"

// // MQTT Broker Settings
// #define MQTT_HOST IPAddress(192,168,0,62)
// #define MQTT_PORT 12345 //1883 
// #define MQTT_PUB_TEMP "klasse1/temp"
// #define MQTT_PUB_MESSAGE "klasse1/message"  // Fixed duplicate topic name

// // DHT11 Settings
// #define DHTPIN 4   // GPIO4
// #define DHTTYPE DHT11
// DHT dht(DHTPIN, DHTTYPE);

// // Objects
// AsyncMqttClient mqttClient;
// Ticker mqttReconnectTimer;
// Ticker wifiReconnectTimer;

// void connectToWifi() {
//   Serial.println("Connecting to Wi-Fi...");
//   IPAddress staticIP(192, 168, 0, 110);  // Use the same IP it’s getting
//   IPAddress gateway(192, 168, 0, 1);     // Your router’s IP
//   IPAddress subnet(255, 255, 255, 0);    // Standard subnet mask
//   IPAddress DNSClient(8,8,8,8);
//   WiFi.config(staticIP, gateway, subnet);
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
// }

// void connectToMqtt() {
//   Serial.println("Attempting MQTT connection...");

//   // Test ping to broker
//   Serial.print("Pinging broker at ");
//   Serial.print(MQTT_HOST);
//   Serial.print(" ... ");
//   if (Ping.ping(MQTT_HOST, 3)) {
//     Serial.println("Ping successful!");
//   } else {
//     Serial.println("Ping failed!");
//   }

//   // Test TCP connection
//   WiFiClient testClient;
//   testClient.setTimeout(5000);
//   Serial.print("Attempting TCP connection to ");
//   Serial.print(MQTT_HOST);
//   Serial.print(":");
//   Serial.println(MQTT_PORT);
//   if (testClient.connect(MQTT_HOST, MQTT_PORT)) {
//     Serial.println("TCP connection to broker succeeded!");
//     testClient.stop();
//   } else {
//     Serial.println("TCP connection to broker failed!");
//     Serial.print("WiFiClient error code: ");
//     Serial.println(testClient.connected() ? "Connected" : "Not connected");
//     Serial.print("WiFi status: ");
//     Serial.println(WiFi.status());
//   }

//   mqttClient.setServer(MQTT_HOST, MQTT_PORT);
//   mqttClient.connect();
// }

// void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info) {
//   Serial.println("WiFi connected!");
//   Serial.print("IP Address: ");
//   Serial.println(WiFi.localIP());
//   connectToMqtt();
// }

// void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
//   Serial.println("WiFi disconnected!");
//   mqttReconnectTimer.detach();  // Stop MQTT reconnect attempts
//   wifiReconnectTimer.once(2, connectToWifi);
// }

// void onMqttConnect(bool sessionPresent) {
//   Serial.println("Connected to MQTT!");
//   Serial.print("Session present: ");
//   Serial.println(sessionPresent);
// }

// void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
//   Serial.print("Disconnected from MQTT. Reason: ");
//   Serial.println((int)reason);
//   if (WiFi.isConnected()) {
//     mqttReconnectTimer.once(2, connectToMqtt);
//   }
// }

// void publishMessage() {
//   if (!mqttClient.connected()) {
//     Serial.println("MQTT not connected. Skipping publish.");
//     return;
//   }

//   float temp = dht.readTemperature();
//   mqttClient.publish(MQTT_PUB_MESSAGE, 0, false, "HELLO FROM ESP32");

//   if (isnan(temp)) {
//     Serial.println("Error reading DHT11 sensor.");
//     mqttClient.publish(MQTT_PUB_TEMP, 0, false, "Sensor Error");
//   } else {
//     Serial.printf("Publishing temperature: %.2f°C\n", temp);
//     mqttClient.publish(MQTT_PUB_TEMP, 0, false, String(temp).c_str());
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   dht.begin();

//   // WiFi event handlers
//   WiFi.onEvent(onWifiConnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
//   WiFi.onEvent(onWifiDisconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

//   // MQTT event handlers
//   mqttClient.onConnect(onMqttConnect);
//   mqttClient.onDisconnect(onMqttDisconnect);

//   connectToWifi();
// }

// void loop() {
//   static unsigned long lastPublish = 0;
//   static unsigned long lastPrintTime = 0;
//   unsigned long currentMillis = millis();

//   if (currentMillis - lastPrintTime >= 5000) {
//     lastPrintTime = currentMillis;
//     float temperature = dht.readTemperature();
//     Serial.print("Temperature is: ");
//     Serial.println(isnan(temperature) ? "Sensor Error" : String(temperature) + "°C");
//   }

//   if (currentMillis - lastPublish >= 10000) {
//     lastPublish = currentMillis;
//     publishMessage();
//   }
// }