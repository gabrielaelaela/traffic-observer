#include "vehicle_counter.h"

VehicleCounter::VehicleCounter(int line) : m_yLine(line) {}

void VehicleCounter::checkVehicle(const Detection& detection) {
    if (detection.label != "car" && detection.label != "truck" && detection.label != "motorbike") return;

    if (!m_previousY.contains(detection.trackId)) {
        m_previousY[detection.trackId] = detection.y;
        return;
    }

    if ((detection.y >= m_yLine) && (m_previousY[detection.trackId] < m_yLine)) {
        if (m_passedIds.contains(detection.trackId)) return;
        m_passedIds.insert(detection.trackId);
        std::string log = "Another car crossed the line (#" 
                            + std::to_string(detection.trackId) 
                            + "). New count: " + std::to_string(m_passedIds.size());
        Logger::write_log(Priority::trace, log);
    }

    m_previousY[detection.trackId] = detection.y;
}

void VehicleCounter::checkVehicle(const std::vector<Detection>& detections) {
    for (const auto& d: detections) {
        checkVehicle(d);
    }
}