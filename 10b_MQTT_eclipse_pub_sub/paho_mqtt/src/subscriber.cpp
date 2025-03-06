#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mqtt/async_client.h>
#include "../sql_utils/sql_utils.h"  // Updated header with table creation

const std::string SERVER_ADDRESS("74c7d5bfb46248ca858248f3b31bb752.s1.eu.hivemq.cloud:8883");
const std::string CLIENT_ID("SubscriberClient");
const char* DB_PATH = "../products.db";  // Configurable database path

class MQTTSubscriber : public virtual mqtt::callback {
private:
    mqtt::async_client client;
    sqlite3* db;  // Database handle

public:
    MQTTSubscriber() 
        : client(SERVER_ADDRESS, CLIENT_ID), db(nullptr) {
        
        // Configure TLS and connection options
        mqtt::ssl_options sslopts;
        sslopts.set_trust_store("certs/ca.crt");  // Path to CA certificate
        sslopts.set_ssl_version(MQTT_SSL_VERSION_TLS_1_2);  // Require TLS 1.2

        mqtt::connect_options connOpts;
        connOpts.set_user_name("anders");           // Replace with your credentials
        connOpts.set_password("Mortensen123!");     // Replace with your credentials
        connOpts.set_clean_session(true);
        connOpts.set_ssl(sslopts);

        // Set callback
        client.set_callback(*this);

        try {
            std::cout << "Connecting to MQTT broker..." << std::endl;
            client.connect(connOpts)->wait();
            std::cout << "Connected to MQTT broker!" << std::endl;

            // Subscribe to topics
            client.subscribe("temp3", 0);
            client.subscribe("humi", 0);
            
            // Open database and create tables
            if (!open_database(&db, DB_PATH)) {
                std::cout << "Failed to open database." << std::endl;
            } else if (!create_tables(db)) {
                std::cout << "Failed to create tables." << std::endl;
                close_database(db);
                db = nullptr;
            }
        } catch (const mqtt::exception& exc) {
            std::cerr << "Connection error: " << exc.what() << std::endl;
        }
    }

    ~MQTTSubscriber() {
        try {
            client.disconnect()->wait();
            std::cout << "Disconnected from MQTT broker." << std::endl;
        } catch (const mqtt::exception& exc) {
            std::cerr << "Disconnect error: " << exc.what() << std::endl;
        }
        
        if (db) {
            close_database(db);
        }
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        std::string device = msg->get_topic();
        std::string value = msg->get_payload_str();

        // Get current timestamp
        time_t now = time(nullptr);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

        std::cout << "Received message on topic " << device 
                  << ": " << value << " at " << timestamp << std::endl;

        // Insert into database
        if (db) {
            if (!insert_measurement(db, device.c_str(), value.c_str(), timestamp)) {
                std::cout << "Failed to insert into database." << std::endl;
            }
        } else {
            std::cout << "Database not open, skipping insert." << std::endl;
        }
    }

    void run() {
        // Keep the application running
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main() {
    std::cout << "TEST 1" << std::endl;

    try {
        MQTTSubscriber subscriber;
        std::cout << "TEST 2" << std::endl;
        
        subscriber.run();
        std::cout << "TEST 3" << std::endl;  // This won't be reached due to run() loop
    } catch (const std::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}