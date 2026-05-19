#include "centroid_tracker.h"

void CentroidTracker::update(std::vector<Detection>& detections) {
    std::map<int, bool> matched;
    
    for (auto& d: detections) {
        cv::Point center(d.x + d.w/2, d.y + d.h/2);

        int bestId = -1;
        float bestDistance = 999999.0f;

        for (auto& [id, oldCenter]: m_objects) {
            if (matched[id]) continue;

            float dist = distance(center, oldCenter);

            if (dist < bestDistance && dist < 50.0f) {
                bestDistance = dist;
                bestId = id;
            }
        }

        if (bestId == -1) bestId = m_nextId++;

        d.trackId = bestId;
        m_objects[bestId] = center;
        matched[bestId] = true;
    }  
}

float CentroidTracker::distance(const cv::Point& a, const cv::Point& b) {
    return cv::norm(a - b);
}