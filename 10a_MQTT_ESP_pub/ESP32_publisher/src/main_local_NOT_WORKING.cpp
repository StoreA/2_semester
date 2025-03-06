// #include <WiFi.h>
// #include <PubSubClient.h>
// #include <DHT.h>

// #define DHTPIN 4          // DHT11 sensor pin
// #define DHTTYPE DHT11     // DHT 11
// #define MQTT_MAX_PACKET_SIZE 256

// // Network credentials
// const char* ssid = "TP-Link_6B21";
// const char* password = "Albatros1920JaTak!";

// // MQTT broker settings
// const char* mqtt_broker_ip = "192.168.0.62";
// const int mqtt_port = 1883;
// const char* mqtt_topic = "temp3";
// const char* mqtt_username = "anders";   // MQTT username
// const char* mqtt_password = "morten";   // MQTT password

// // Static IP settings
// IPAddress local_IP(192, 168, 0, 110);
// IPAddress gateway(192, 168, 0, 1);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress dns(8, 8, 8, 8);



// WiFiClient espClient;
// PubSubClient client(espClient);
// DHT dht(DHTPIN, DHTTYPE);

// void connectToMQTT() {
//   while (!client.connected()) {
//     if (espClient.connected()) {
//       espClient.stop();  // Force close socket
//       delay(100);
//     }

//     Serial.println("Flushing TCP Buffers...");
//     espClient.flush();  // Force flush

//     String client_id = "esp32-client-";
//     client_id += String(WiFi.macAddress());
//     Serial.print("Attempting MQTT connection...");

//     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
//       Serial.println("Connected to MQTT Broker");
//     } else {
//       Serial.print("Failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" Trying again in 5 seconds");
//       delay(5000);
//     }
//   }
// }

// void setup() {


//   Serial.begin(115200);


//   WiFi.mode(WIFI_STA);
//   WiFi.setSleep(false); // Disable power save

//   if (!WiFi.config(local_IP, gateway, subnet, dns)) {
//     Serial.println("Failed to configure Static IP");
//   }
  

//   WiFi.setHostname("esp32-client");
//   espClient.setTimeout(200);
//   WiFi.disconnect(true);
//   delay(100);
//   WiFi.begin(ssid, password);
//   delay(1000);

//   if (WiFi.waitForConnectResult() != WL_CONNECTED) {
//     Serial.println("WiFi Failed to Connect");
//     return;
//   }

//   Serial.println("Connected to WiFi");
//   Serial.print("Broker IP: ");
//   Serial.println(mqtt_broker_ip);
//   Serial.print("ESP32 IP: ");
//   Serial.println(WiFi.localIP());

//   client.setServer(mqtt_broker_ip, mqtt_port);
//   client.setKeepAlive(60);

//   connectToMQTT();
//   dht.begin();
// }

// void loop() {
//   if (!client.connected()) {
//     connectToMQTT();
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

//   Serial.println("There is connection through from the ESP32.");
//   Serial.print("Published: ");
//   Serial.println(payload);

//   delay(2000);
// }
