#include "mqtt_publisher.h"

MqttPublisher::MqttPublisher(const std::string& server
                            , const std::string& clientId
                            , const std::string& topic)
                            : m_client(server, clientId)
                            , m_topic(topic)
{
    m_client.connect()->wait();
}

void MqttPublisher::publish(int trackId, const std::string& vehicleType) {
    std::string payload =
        "{"
        "\"event\":\"vehicle_crossed\","
        "\"track_id\":" + std::to_string(trackId) + ","
        "\"vehicle_type\":\"" + vehicleType + "\""
        "}";

    auto msg = mqtt::make_message(
        m_topic,
        payload
    );

    msg->set_qos(1);

    m_client.publish(msg);
}