#pragma once
#include <set>
#include <string>
#include <vector>
#include "core/types/detection.h"
#include "logger/logger.h"
#include "messaging/mqtt/mqtt_publisher.h"

class VehicleCounter {
public:
    VehicleCounter() = delete;
    VehicleCounter(int line, std::shared_ptr<MqttPublisher> publisher);
    void checkVehicle(const Detection& d);
    void checkVehicle(const std::vector<Detection>& d);

private:
    int m_yLine = -1;
    std::shared_ptr<MqttPublisher> m_publisher;
    std::set<int> m_passedIds;
    std::unordered_map<int, int> m_previousY;
};