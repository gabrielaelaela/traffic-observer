#pragma once
#include <set>
#include <string>
#include <vector>
#include "core/types/detection.h"
#include "logger/logger.h"

class VehicleCounter {
public:
    explicit VehicleCounter(int line);
    void checkVehicle(const Detection& d);
    void checkVehicle(const std::vector<Detection>& d);

private:
    int m_yLine = -1;
    std::set<int> m_passedIds;
    std::unordered_map<int, int> m_previousY;
};