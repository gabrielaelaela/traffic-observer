#pragma once
#include "core/frame.h"

class IProcessor {
public:
    virtual void process(Frame& frame) = 0;
    virtual ~IProcessor() = default;
};