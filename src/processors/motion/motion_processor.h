#pragma once

#include <vector>
#include "core/frame.h"
#include "core/pipeline/iprocessor.h"
#include "logger/logger.h"
#include <iostream>

class MotionProcessor : public IProcessor {
public:
    void process(Frame& frame) override;

private:
    std::vector<unsigned char> m_prev_frame;
    bool m_first_frame = true;
};