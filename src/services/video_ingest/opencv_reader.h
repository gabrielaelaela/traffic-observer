#pragma once
#include <cstdint>
#include <opencv2/opencv.hpp>
#include "ivideo_reader.h"
#include "logger/logger.h"
#include <string>

class OpenCVReader : public IVideoReader {
public:
    OpenCVReader() = delete;
    explicit OpenCVReader(const std::string& filename);

    bool start() override;
    bool read(Frame& frame) override;
    void stop() override;

    ~OpenCVReader() override;

private:
    std::string m_filename;
    cv::VideoCapture m_cap;
    cv::Mat m_mat;
    bool m_ret = false;
    bool m_started = false;
};