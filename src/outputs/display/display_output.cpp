#include "display_output.h"

void DisplayOutput::send(const Frame& frame) {
    uchar type;
    if (frame.channels == 1) type = CV_8UC1;
    else type = CV_8UC3;
    cv::Mat displayMat(frame.height, frame.width, type);
    std::memcpy(displayMat.data, frame.data.data(), frame.data.size());

    for (auto& d : frame.detections) {
        cv::rectangle(
            displayMat,
            cv::Rect(
                d.x,
                d.y,
                d.w,
                d.h
            ),
            cv::Scalar(0, 255, 0),
            2
        );

        cv::putText(
            displayMat,
            d.label,
            cv::Point(d.x, d.y),
            cv::FONT_HERSHEY_SIMPLEX,
            0.5,
            cv::Scalar(0, 255, 0),
            1
        );
    }

    cv::namedWindow("First frame", cv::WINDOW_NORMAL);
    cv::imshow("First frame", displayMat);
    cv::waitKey(1);
}