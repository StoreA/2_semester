#include <mosquittopp.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include "../sql_utils/sql_utils.h"


class MQTTSubscriber : public mosqpp::mosquittopp
{
private:
    sqlite3 *db; // Database handle

public:
    MQTTSubscriber(const char *id, const char *host, int port) : mosquittopp(id)
    {
        // Enable TLS and specify the CA certificate
        tls_set("certs/ca.crt", NULL, NULL, NULL, NULL);
        tls_opts_set(1, "tlsv1.2", NULL); // Require TLS 1.2 (HiveMQ Cloud requirement)

        // Set username and password for HiveMQ Cloud
        username_pw_set("anders", "Mortensen123!"); // Replace with your actual credentials

        // Connect to the broker
        connect(host, port, 60);
        db = nullptr; // Initialize database pointer
    }

    ~MQTTSubscriber()
    {
        if (db) {
            close_database(db); // Clean up database
        }
    }

    void on_connect(int rc)
    {
        if (rc == 0) {
            std::cout << "Connected to MQTT broker." << std::endl;
            subscribe(NULL, "temp3");
            subscribe(NULL, "humi"); // Subscribe to both topics
            // Open database on connect
            if (!open_database(&db)) {
                std::cout << "Failed to open database." << std::endl;
            }
        } else {
            std::cout << "Failed to connect. RC: " << rc << std::endl;
        }
    }

    void on_message(const struct mosquitto_message *message)
    {
        if (message->payloadlen) {
            // Use topic as device (e.g., "temp3" or "humi")
            std::string device(message->topic);

            // Convert payload to string (e.g., "23.5")
            std::string payload(static_cast<char*>(message->payload), message->payloadlen);
            std::string value = payload;

            // Get current timestamp
            time_t now = time(nullptr);
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

            std::cout << "Received message on topic " << message->topic 
                      << ": " << value << " at " << timestamp << std::endl;

            // Insert into database
            if (db) {
                if (!insert_measurement(db, device.c_str(), value.c_str(), timestamp)) {
                    std::cout << "Failed to insert into database." << std::endl;
                }
            } else {
                std::cout << "Database not open, skipping insert." << std::endl;
            }
        } else {
            std::cout << "Received empty message on topic " << message->topic << std::endl;
        }
    }
};

int main()
{
    const char *host = "74c7d5bfb46248ca858248f3b31bb752.s1.eu.hivemq.cloud"; // Replace with your HiveMQ Cloud host
    int port = 8883; // TLS port
    printf("TEST 1");

    mosqpp::lib_init();
    printf("TEST 2");

    MQTTSubscriber subscriber("subscriber", host, port);
    printf("TEST 3");

    while (true) {
        subscriber.loop();
        sleep(1);
        printf("TEST 4");
    }

    mosqpp::lib_cleanup();

    return 0;
}