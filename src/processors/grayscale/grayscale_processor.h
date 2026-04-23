#pragma once
#include "core/pipeline/iprocessor.h"
#include <opencv2/opencv.hpp>

class GrayscaleProcessor : public IProcessor {
public:
    void process(Frame& frame) override;
};