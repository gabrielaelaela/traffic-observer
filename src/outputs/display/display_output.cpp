#include "display_output.h"

void DisplayOutput::send(const Frame& frame) {
    uchar type;
    if (frame.channels == 1) type = CV_8UC1;
    else type = CV_8UC3;
    cv::Mat displayMat(frame.height, frame.width, type);
    std::memcpy(displayMat.data, frame.data.data(), frame.data.size());

    cv::namedWindow("First frame", cv::WINDOW_NORMAL);
    cv::imshow("First frame", displayMat);
    cv::waitKey(10);
}