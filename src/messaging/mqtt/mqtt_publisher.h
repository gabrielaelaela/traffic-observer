#pragma once
#include <string>
#include <mqtt/async_client.h>
#include <iostream>

class MqttPublisher {
public:
    MqttPublisher(const std::string& server, const std::string& clientId, const std::string& topic);
    void publish(int trackId, const std::string& vehicleType);

private:
    mqtt::async_client m_client;
    std::string m_topic;
};