#pragma once
#include "core/types/frame.h"

class IVideoReader {
public:
    virtual bool start() = 0;
    virtual bool read(Frame& frame) = 0;
    virtual void stop() = 0;
    virtual ~IVideoReader() = default;
};