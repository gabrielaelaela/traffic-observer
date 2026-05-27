#pragma once
#include <opencv2/dnn.hpp>
#include<opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "core/pipeline/iprocessor.h"
#include "logger/logger.h"
#include "trackers/centroid/centroid_tracker.h"
#include "analytics/vehicle_counter.h"

class YoloProcessor : public IProcessor {
public:
    explicit YoloProcessor(const std::string& cfg, const std::string& weights, const std::string& names);

    void process(Frame& frame) override;

private:
    cv::dnn::Net m_net;
    std::vector<std::string> m_classes;
    CentroidTracker m_tracker;
    VehicleCounter m_counter{500};
};