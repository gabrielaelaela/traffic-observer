#pragma once
#include "core/frame.h"

class IVideoReader {
public:
    virtual bool start() = 0;
    virtual bool read(Frame& frame) = 0;
    virtual void stop() = 0;
    virtual bool display() = 0;
    virtual ~IVideoReader() = default;
};