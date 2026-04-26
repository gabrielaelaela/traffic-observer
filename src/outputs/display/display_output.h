#pragma once
#include <cstdint>
#include <opencv2/opencv.hpp>
#include "core/pipeline/ioutput.h"

class DisplayOutput: public IOutput {
public:
    void send(const Frame& frame) override;
};