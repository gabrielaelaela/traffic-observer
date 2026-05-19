#pragma once
#include <vector>
#include <map>
#include <opencv2/opencv.hpp>
#include "core/types/detection.h"

class CentroidTracker {
public:
    void update(std::vector<Detection>& detections);

private:
    size_t m_nextId = 0;
    std::map<int, cv::Point> m_objects;

    float distance(const cv::Point& a, const cv::Point& b);
};