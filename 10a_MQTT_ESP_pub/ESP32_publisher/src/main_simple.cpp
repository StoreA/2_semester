// #include <WiFi.h>

// const char* ssid = "TP-Link_6B21";
// const char* password = "Albatros1920JaTak!";

// void setup() {
//   Serial.begin(115200);
//   WiFi.disconnect(true);
//   delay(1000);

//   WiFi.begin(ssid, password);
//   Serial.print("Connecting");
//   int attempts = 0;
//   while (WiFi.status() != WL_CONNECTED && attempts < 20) {
//     delay(1000);
//     Serial.print(".");
//     attempts++;
//   }
//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("\nConnected");
//     Serial.print("IP address: ");
//     Serial.println(WiFi.localIP());
//   } else {
//     Serial.println("\nFailed to connect");
//   }
// }

// void loop() {}
