#pragma once
#include "core/frame.h"

class IOutput {
public:
    virtual void send(const Frame& frame) = 0;
    virtual ~IOutput() = default;
};