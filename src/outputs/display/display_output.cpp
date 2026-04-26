#include "display_output.h"

void DisplayOutput::send(const Frame& frame) {
    cv::Mat displayMat(frame.height, frame.width, CV_8UC3);
    std::memcpy(displayMat.data, frame.data.data(), frame.data.size());

    cv::namedWindow("First frame", cv::WINDOW_NORMAL);
    cv::imshow("First frame", displayMat);
    cv::waitKey(10);
}