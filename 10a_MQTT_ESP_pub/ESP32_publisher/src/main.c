// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_wifi.h"
// #include "esp_event.h"
// #include "nvs_flash.h"
// #include "lwip/sockets.h"
// #include "lwip/inet.h"  // For inet_addr

// #define WIFI_SSID "TP-Link_6B21"
// #define WIFI_PASS "Albatros1920JaTak!"

// static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
//     if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
//         esp_wifi_connect();
//     } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
//         printf("WiFi disconnected, retrying...\n");
//         esp_wifi_connect();
//     } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
//         ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
//         char ip_str[16];
//         snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", 
//                  (event->ip_info.ip.addr >> 0) & 0xFF,
//                  (event->ip_info.ip.addr >> 8) & 0xFF,
//                  (event->ip_info.ip.addr >> 16) & 0xFF,
//                  (event->ip_info.ip.addr >> 24) & 0xFF);
//         printf("Got IP: %s\n", ip_str);
//     }
// }

// void test_tcp() {
//     struct sockaddr_in server_addr;
//     int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
//     if (sock < 0) {
//         printf("Socket creation failed: %d\n", errno);
//         return;
//     }

//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(80);
//     server_addr.sin_addr.s_addr = inet_addr("8.8.8.8");

//     printf("Connecting to 8.8.8.8:80...\n");
//     if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
//         printf("TCP connection succeeded!\n");
//         close(sock);
//     } else {
//         printf("TCP connection failed! Error: %d\n", errno);
//         close(sock);
//     }
// }

// void app_main(void) {
//     esp_err_t ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//         nvs_flash_erase();
//         nvs_flash_init();
//     }

//     esp_netif_init();
//     esp_event_loop_create_default();
//     esp_netif_create_default_wifi_sta();

//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     esp_wifi_init(&cfg);

//     esp_event_handler_instance_t instance_any_id;
//     esp_event_handler_instance_t instance_got_ip;
//     esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id);
//     esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip);

//     wifi_config_t wifi_config = {
//         .sta = {
//             .ssid = WIFI_SSID,
//             .password = WIFI_PASS,
//         },
//     };
//     esp_wifi_set_mode(WIFI_MODE_STA);
//     esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
//     esp_wifi_start();

//     while (true) {
//         vTaskDelay(5000 / portTICK_PERIOD_MS);
//         test_tcp();
//     }
// }