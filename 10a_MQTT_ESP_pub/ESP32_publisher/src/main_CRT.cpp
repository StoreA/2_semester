// #include <WiFi.h>
// #include <WiFiClientSecure.h>  // Changed to secure client
// #include <AsyncMqttClient.h>
// #include <DHT.h>

// #define DHTPIN 4
// #define DHTTYPE DHT11

// const char* ssid = "TP-Link_6B21";
// const char* password = "Albatros1920JaTak!";
// const char* mqtt_broker_ip = "74c7d5bfb46248ca858248f3b31bb752.s1.eu.hivemq.cloud";
// const int mqtt_port = 8883;
// const char* mqtt_topic = "temp3";
// const char* mqtt_username = "anders";
// const char* mqtt_password = "Mortensen123!";

// // HiveMQ certificate
// const char* ca_cert = \
// "-----BEGIN CERTIFICATE-----\n" \
// "MIIFDDCCA/SgAwIBAgISBMta5F9baTiGGVMMyyIfyuJOMA0GCSqGSIb3DQEBCwUA\n" \
// "MDMxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQwwCgYDVQQD\n" \
// "EwNSMTEwHhcNMjUwMjIxMjE1NDMyWhcNMjUwNTIyMjE1NDMxWjAfMR0wGwYDVQQD\n" \
// "DBQqLnMxLmV1LmhpdmVtcS5jbG91ZDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\n" \
// "AQoCggEBAKVuz2sMPmxx2w/f81/YAEKTbNZMJPk2+ooLFg5hxXvReF+AwIT4XvZ+\n" \
// "MLhSKvFxmghJF+BB9WyhqrcJLGDCP4s6SOLWTYixEoTcaLUviqqn+06kYqDJ6E83\n" \
// "NGsc7T42DlPnzqcZZjPRed9rt4CP3RgeZlWyYZgiD8FoJG9gie8ytihF/FkGZT8T\n" \
// "N4Vkl2vQa3mfBWeeKrcuhcLPxqIWDz/30iYfLtEe5JYYScoCKTXcP9SUStjpR8pD\n" \
// "vfOWdvasOAuBy7yBbx01/4lcQt50hfbhTR/K14/D4rNkuuvU7ktSQnoxVXC8YDwG\n" \
// "zkny10DFt65mVYLNZcBQtOLHHOZGV30CAwEAAaOCAiwwggIoMA4GA1UdDwEB/wQE\n" \
// "AwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwDAYDVR0TAQH/BAIw\n" \
// "ADAdBgNVHQ4EFgQUgsEjDU35+EWJKBsFxJ0lM0PXMi4wHwYDVR0jBBgwFoAUxc9G\n" \
// "pOr0w8B6bJXELbBeki8m47kwVwYIKwYBBQUHAQEESzBJMCIGCCsGAQUFBzABhhZo\n" \
// "dHRwOi8vcjExLm8ubGVuY3Iub3JnMCMGCCsGAQUFBzAChhdodHRwOi8vcjExLmku\n" \
// "bGVuY3Iub3JnLzAzBgNVHREELDAqghQqLnMxLmV1LmhpdmVtcS5jbG91ZIISczEu\n" \
// "ZXUuaGl2ZW1xLmNsb3VkMBMGA1UdIAQMMAowCAYGZ4EMAQIBMIIBBAYKKwYBBAHW\n" \
// "eQIEAgSB9QSB8gDwAHYAouMK5EXvva2bfjjtR2d3U9eCW4SU1yteGyzEuVCkR+cA\n" \
// "AAGVKrbguQAABAMARzBFAiAu8e2AhMVBQ20Ho/VdVn0O1hND8cahMS5LNp4i+d22\n" \
// "gAIhALfY7HqznFKIV/9pMFwir1M2dofh2iuXrNc2NT/G23uXAHYAzxFW7tUufK/z\n" \
// "h1vZaS6b6RpxZ0qwF+ysAdJbd87MOwgAAAGVKrbg+gAABAMARzBFAiEA5t4gaB9/\n" \
// "9ReLvpUAVUvdUHtNs1yCVNXGaFhwZcBnrxACIGjbFQ8HCCdkrXNVpsaOg9HC+LhI\n" \
// "XL6S09i9lgRnwUgLMA0GCSqGSIb3DQEBCwUAA4IBAQBNfUjHftHJ4ZUIIvR5SgyN\n" \
// "LbyvcJsR1DeM1QyzRy/lDaLaD58/nSghNTkdwTDZxkl6VsGslqL2wsEAT/6l31TF\n" \
// "1JaqlP531rEplNgZfwbhj+LlcKWPBi3KkN7hg90UXCWA5iR7uIs0ntgolkNB/1S2\n" \
// "aPAaWI226YEzf/tHhuOxsQwyPSSAOd47G0dIuayZycqDKnuaeORKJdnEckp93+Kr\n" \
// "3xixQoJD2m04l2tgKd9j/gTA9GGncMedJI96XlaQkv9O2+q/WZdPiRYS9GMwsqnz\n" \
// "E0rmnWfEB2gMwZ9xwFFJKAewSVjMkjvOWjEGnG9OcSkZIkqumUy88ooisl/mAQuA\n" \
// "-----END CERTIFICATE-----\n";

// AsyncMqttClient mqttClient;
// WiFiClientSecure wifiClient;  // Changed to secure client
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
//   wifiClient.setInsecure();  // For testing only
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
  
//   // Configure SSL
//   wifiClient.setCACert(ca_cert);
  
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