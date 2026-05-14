#pragma once
#include "core/types/frame.h"

class IProcessor {
public:
    virtual void process(Frame& frame) = 0;
    virtual ~IProcessor() = default;
};