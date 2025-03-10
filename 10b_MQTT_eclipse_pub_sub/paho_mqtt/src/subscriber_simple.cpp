#include <iostream>
#include <string>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS("tcp://74c7d5bfb46248ca858248f3b31bb752.s1.eu.hivemq.cloud:1883");  // Correct for TCP-TLS
const std::string CLIENT_ID("MQTT_Subscriber_Debian");
const std::string MQTT_USER("anders");
const std::string MQTT_PASS("Mortensen123!");  // Replace with actual password

class MessageCallback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message received on topic [" << msg->get_topic() << "]: " 
                  << msg->to_string() << std::endl;
    }
};

int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    MessageCallback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);
    connOpts.set_user_name(MQTT_USER);
    connOpts.set_password(MQTT_PASS);

    try {
        // Connect to the broker
        client.connect(connOpts)->wait();
        std::cout << "Connected to MQTT broker!" << std::endl;

        // Subscribe to multiple topics with QoS 1
        client.subscribe("temp3", 0);
        client.subscribe("humi", 0);

        // Keep running indefinitely
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
