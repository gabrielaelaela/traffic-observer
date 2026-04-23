#include "grayscale_processor.h"

void GrayscaleProcessor::process(Frame& frame) {

    cv::Mat colorImg(frame.height, frame.width, CV_8UC3, frame.data.data());
    cv::Mat grayImg;

    cv::cvtColor(colorImg, grayImg, cv::COLOR_BGR2GRAY);

    frame.width = grayImg.cols;
    frame.height = grayImg.rows;
    frame.data.assign(grayImg.data, grayImg.data + grayImg.total() * grayImg.elemSize());
}