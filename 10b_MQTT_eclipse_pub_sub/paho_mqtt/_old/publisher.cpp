#include <iostream>
#include <string>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS("tcp://74c7d5bfb46248ca858248f3b31bb752.s1.eu.hivemq.cloud:8883");
const std::string CLIENT_ID("ExampleClient");

int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        client.connect(connOpts)->wait();
        std::cout << "Connected to the MQTT broker!" << std::endl;

        const std::string topic("temp3");
        const std::string payload("Hello, MQTT!");
        client.publish(topic, payload.data(), payload.size(), 0, false);
        std::cout << "Message published!" << std::endl;

        client.disconnect()->wait();
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    return 0;
}