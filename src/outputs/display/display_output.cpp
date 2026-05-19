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
            cv::Scalar(0, 0, 255),
            2
        );

        cv::putText(
            displayMat,
            d.label + " #" + std::to_string(d.trackId),
            cv::Point(d.x, d.y - 5),
            cv::FONT_HERSHEY_SIMPLEX,
            0.5,
            cv::Scalar(0, 0, 255),
            1
        );
    }

    cv::namedWindow("First frame", cv::WINDOW_NORMAL);
    cv::imshow("First frame", displayMat);
    cv::waitKey(1);
}