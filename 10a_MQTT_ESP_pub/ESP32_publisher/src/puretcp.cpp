// #include <Arduino.h>
// #include <WiFi.h>
// #include <WiFiUdp.h>

// const char* ssid = "TP-Link_6B21";
// const char* password = "Albatros1920JaTak!";

// WiFiUDP udp;

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
//   Serial.println("Starting...");

//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nWiFi connected");
//   Serial.print("IP Address: ");
//   Serial.println(WiFi.localIP());

//   udp.begin(1234);
//   Serial.println("Testing UDP to 8.8.8.8:1234...");
//   udp.beginPacket("8.8.8.8", 1234);
//   udp.write("Hello UDP");
//   if (udp.endPacket()) {
//     Serial.println("UDP packet sent successfully!");
//   } else {
//     Serial.println("UDP packet send failed!");
//   }
// }

// void loop() {
//   delay(5000);
//   Serial.println("Loop running...");
// }