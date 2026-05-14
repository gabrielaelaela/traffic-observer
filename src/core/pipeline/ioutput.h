#pragma once
#include "core/types/frame.h"

class IOutput {
public:
    virtual void send(const Frame& frame) = 0;
    virtual ~IOutput() = default;
};