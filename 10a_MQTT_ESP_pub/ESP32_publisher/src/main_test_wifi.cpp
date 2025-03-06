// #include <WiFi.h>
// #include <PubSubClient.h>
// #include <DHT.h>

// #define DHTPIN 4          // DHT11 sensor pin
// #define DHTTYPE DHT11     // DHT 11

// // Network credentials
// const char* ssid = "TP-Link6B21";
// const char* password = "";

// // MQTT broker settings
// const char* mqtt_broker_ip = "192.168.0.62";
// const int mqtt_port = 1883;
// const char* mqtt_topic = "klasse1/temp";
// const char* mqtt_username = "anders";   // MQTT username
// const char* mqtt_password = "morten";   // MQTT password

// WiFiClient espClient;
// PubSubClient client(espClient);
// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(115200);

//   WiFi.mode(WIFI_STA);
//   WiFi.disconnect(true);  // Erase old WiFi config
//   delay(1000);

//   WiFi.begin(ssid, password);

//   Serial.print("Connecting to WiFi");
//   int attempts = 0;
//   while (WiFi.status() != WL_CONNECTED && attempts < 20) {
//     delay(1000);
//     Serial.print(".");
//     attempts++;
//   }
//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("\nConnected to WiFi");
//   } else {
//     Serial.println("\nFailed to connect to WiFi");
//     return;
//   }

//   client.setServer(mqtt_broker_ip, mqtt_port);

//   while (!client.connected()) {
//     String client_id = "esp32-client-";
//     client_id += String(WiFi.macAddress());
//     Serial.print("Attempting MQTT connection...");

//     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
//       Serial.println("connected");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       delay(5000);
//     }
//   }

//   dht.begin();
// }

// void loop() {
//   if (!client.connected()) {
//     while (!client.connected()) {
//       String client_id = "esp32-client-";
//       client_id += String(WiFi.macAddress());
//       Serial.print("Attempting MQTT connection...");

//       if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
//         Serial.println("connected");
//       } else {
//         Serial.print("failed, rc=");
//         Serial.print(client.state());
//         Serial.println(" try again in 5 seconds");
//         delay(5000);
//       }
//     }
//   }
//   client.loop();

//   float humidity = dht.readHumidity();
//   float temperature = dht.readTemperature();

//   if (isnan(humidity) || isnan(temperature)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }

//   String payload = "Temperature: " + String(temperature) + " C, Humidity: " + String(humidity) + " %";
//   client.publish(mqtt_topic, payload.c_str());

//   Serial.print("Published: ");
//   Serial.println(payload);

//   delay(2000);
// }
